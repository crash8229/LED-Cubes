import construct

frame_v1 = construct.BitStruct("secondary_header" / construct.Struct("duration" / construct.Bytewise(construct.BytesInteger(2)), "data_length" / construct.Bytewise(construct.BytesInteger(2))), "tlc_states" / construct.Array(construct.this.secondary_header.data_length // 24, construct.Struct("state" / construct.Array(16, construct.BitsInteger(12)))))
