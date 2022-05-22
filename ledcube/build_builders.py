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


def _check_array(field: dict, seq_ids: Iterable[str]) -> Tuple[bool, Union[int, str]]:
    array = False
    array_size: Union[int, str] = 0
    if "repeat" in field:
        array = True
        if "expr" in field["repeat"]:
            array_size = _get_array_size(field['repeat-expr'], seq_ids)
    return array, array_size


def _get_array_size(repeat: str, ids: Iterable[str]) -> Union[str, int]:
    if isinstance(repeat, str):
        for seq_id in ids:
            if seq_id in repeat:
                idx = repeat.index(seq_id)
                repeat = f"{repeat[:idx-1 if idx else idx]}construct.this.{repeat[idx:]}"
                repeat = repeat.replace("/", "//")
        return repeat
    else:
        return repeat


def _process_seq(seq: dict, types) -> str:
    struct_fields = str()
    seq_ids: Set[str] = set()
    for field in seq:
        field_type = types.get_type(field["type"])

        # Check if it is an array
        array, array_size = _check_array(field, seq_ids)

        if array:
            struct_field = f"{field_type}"
            struct_fields += f"\"{field['id']}\" / {ARRAY_STR.substitute(size=array_size, element=struct_field)}, "
        else:
            struct_field = f"\"{field['id']}\" / {field_type}"
            struct_fields += f"{struct_field}, "

        seq_ids.add(field['id'])
    return struct_fields


def _process_ksy(ksy_file: Path) -> Tuple[str, str]:
    ksy_dir = ksy_file.parent
    with open(ksy_file, "r") as f:
        yaml_data = load(f)

    # Get types and any custom types
    if "types" in yaml_data:
        types = Types(yaml_data["types"])
    else:
        types = Types()

    # Process seq tag
    struct_fields = _process_seq(yaml_data["seq"], types)

    # Build the final struct
    return yaml_data['meta']['id'], STRUCT_STR.substitute(fields=struct_fields[:-2])


class Types():
    __types: Dict[str, Template] = {
        "u": Template("construct.Bytewise(construct.BytesInteger(${num}))"),
        "b": Template("construct.BitsInteger(${num})")
    }

    def __init__(self, custom_types: dict = dict()) -> None:
        self.__custom_types: Dict[str, str] = dict()
        self.__build_types(custom_types)

    def get_type(self, type_str: str) -> Union[str, Template]:
        if type_str in self.__custom_types:
            return self.__custom_types[type_str]

        key = type_str[0]
        num = type_str[1:]
        if key in self.__types:
            return self.__types[key].substitute(num = num)
        else:
            raise ValueError(f"Unknown type string: {type_str}")

    def __build_types(self, data: dict) -> None:
        for type_key in data.keys():
            # Process seq tag
            struct_fields = _process_seq(data[type_key]["seq"], self)

            self.__custom_types[type_key] = STRUCT_STR.substitute(fields = struct_fields[:-2])


def construct_builders(yaml_files: Iterable[Path], output_directory: Path = out_dir) -> Path:
    # Assemble builders
    builders = list()
    for yaml_file in yaml_files:
        seq_name, seq_type = _process_ksy(yaml_file)
        builders.append(f"{seq_name} = {BITWISE_STR.substitute(item=seq_type)}")

    # Write the builder moddule
    out_path = output_directory.joinpath("builder.py")
    with open(out_path, "w") as out:
        out.write("import construct\n\n")
        for builder in builders:
            out.write(f"{builder}\n")

    return out_path


if __name__ == "__main__":

    construct_builders((Path("../doc/file_specification/objects/frame/frame_v1.ksy"),))
    pass

