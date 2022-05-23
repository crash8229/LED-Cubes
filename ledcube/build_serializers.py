from yaml import safe_load as load
from os import mkdir
from pathlib import Path
from typing import Dict, Set, Union, Optional, Tuple, List, Iterable
from string import Template


out_dir = Path("ledcube")

try:
    mkdir(out_dir)
except FileExistsError:
    pass


# Construct templates
STRUCT_STR = Template("construct.Struct(${fields})")
ARRAY_STR = Template("construct.Array(${size}, ${element})")
BITWISE_STR = Template("construct.Bitwise(${item})")
SWITCH_STR = Template("construct.Switch(${switch}, ${cases})")


class Serializer():
    class Types():
        __types: Dict[str, Template] = {
            "u": Template("construct.Bytewise(construct.BytesInteger(${num}))"),
            "b": Template("construct.BitsInteger(${num})"),
            "str": Template("construct.Bytewise(construct.PaddedString(${size}, 'utf8'))")
        }

        def __init__(self) -> None:
            self.__custom_types: Dict[str, str] = dict()
            self.__imports: Dict[str, str] = dict()

        @property
        def imports(self) -> Dict[str, str]:
            return self.__imports.copy()

        def get_type(self, type_str: Union[str, dict], seq_ids: Iterable[str], size: int = 0) -> str:
            if isinstance(type_str, dict):
                if "switch-on" in type_str:
                    return SWITCH_STR.substitute(switch=self._process_expr_str(type_str["switch-on"], seq_ids), cases=self._process_switch_cases(type_str["cases"], seq_ids, self))

            elif isinstance(type_str, str):
                if type_str in self.__imports:
                    return self.__imports[type_str]
                if type_str in self.__custom_types:
                    return self.__custom_types[type_str]


                if type_str in self.__types:
                    if type_str == "str":
                        return self.__types[type_str].substitute(size = size)
                elif type_str[0] in self.__types:
                    key = type_str[0]
                    num = type_str[1:]
                    return self.__types[key].substitute(num = num)

            raise TypeError(f"Unknown type entry: {type_str}")

        def build_types(self, data: dict) -> None:
            for type_key in data.keys():
                # Process seq tag
                struct_fields = Serializer._process_seq(data[type_key]["seq"], self)

                self.__custom_types[type_key] = STRUCT_STR.substitute(fields = struct_fields[:-2])

        def build_imports(self, base_dir: Path, import_files: Iterable[str]) -> None:
            for import_file in import_files:
                seq_name, seq_type, seq_imports = Serializer._process_ksy(base_dir.joinpath(f"{import_file}.ksy"))
                self.__imports[seq_name] = seq_type

        # TODO: Support enums types
        def build_enums(self, data: dict):
            pass

        @staticmethod
        def _process_switch_cases(cases: dict, seq_ids: Iterable[str], types) -> str:
            case_str = Template("${key}: ${value}, ")
            result = "{"
            for key, value in cases.items():
                result += case_str.substitute(key=key, value=types.get_type(value, seq_ids))
            return result[:-2] + "}"

        @staticmethod
        def _process_expr_str(expr_str: str, seq_ids: Iterable[str]) -> str:
            for seq_id in seq_ids:
                if seq_id in expr_str:
                    idx = expr_str.index(seq_id)
                    expr_str = f"{expr_str[:idx-1 if idx else idx]}construct.this.{expr_str[idx:]}"
            return expr_str.replace("/", "//")

        @staticmethod
        def _check_array(field: dict, seq_ids: Iterable[str]) -> Tuple[bool, Union[int, str]]:
            array = False
            array_size: Union[int, str] = 0
            if "repeat" in field:
                array = True
                if "expr" in field["repeat"]:
                    array_size = Serializer.Types._get_array_size(field['repeat-expr'], seq_ids)
            return array, array_size

        @staticmethod
        def _get_array_size(repeat: str, ids: Iterable[str]) -> Union[str, int]:
            if isinstance(repeat, str):
                return Serializer.Types._process_expr_str(repeat, ids)
            else:
                return repeat


    def __init__(self,output_directory: Path = out_dir) -> None:
        self.output_directory = output_directory

    def construct_serializers(self, ksy_files: Iterable[Path]) -> Path:
        # Assemble serializers
        serializers = dict()
        for yaml_file in ksy_files:
            seq_name, seq_type, seq_imports = self._process_ksy(yaml_file)
            serializers.update(seq_imports)
            serializers[seq_name] = seq_type

        # Write the serializer module
        out_path = self.output_directory.joinpath("serializer.py")
        with open(out_path, "w") as out:
            out.write("import construct\n\n")
            for seq_name, seq_type in serializers.items():
                out.write(f"{seq_name} = {BITWISE_STR.substitute(item=seq_type)}\n")

        return out_path

    @staticmethod
    def _process_ksy(ksy_file: Path) -> Tuple[str, str, Dict[str, str]]:
        ksy_dir = ksy_file.parent
        with open(ksy_file, "r") as f:
            yaml_data = load(f)

        # Get types and any custom types
        types = Serializer.Types()
        if "imports" in yaml_data["meta"]:
            types.build_imports(ksy_dir, yaml_data["meta"]["imports"])
        if "types" in yaml_data:
            types.build_types(yaml_data["types"])


        # Process seq tag
        struct_fields = Serializer._process_seq(yaml_data["seq"], types)

        # Build the final struct
        return yaml_data['meta']['id'], STRUCT_STR.substitute(fields=struct_fields[:-2]), types.imports

    @staticmethod
    def _process_seq(seq: dict, types) -> str:
        struct_fields = str()
        seq_ids: Set[str] = set()
        for field in seq:
            field_type = types.get_type(field["type"], seq_ids, field["size"] if "size" in field else 0)

            # Check if it is an array
            array, array_size = Serializer.Types._check_array(field, seq_ids)

            if array:
                struct_field = f"{field_type}"
                struct_fields += f"\"{field['id']}\" / {ARRAY_STR.substitute(size=array_size, element=struct_field)}, "
            else:
                struct_field = f"\"{field['id']}\" / {field_type}"
                struct_fields += f"{struct_field}, "

            seq_ids.add(field['id'])
        return struct_fields


if __name__ == "__main__":
    Serializer().construct_serializers(
        (
            Path("../doc/file_specification/objects/frame.ksy"),
            Path("../doc/file_specification/objects/animation.ksy"),
            Path("../doc/file_specification/objects/library.ksy"),
            Path("../doc/file_specification/objects/cube_file.ksy")
        )
    )
