import construct

primary_header = construct.Bitwise(construct.Struct("type" / construct.Bytewise(construct.BytesInteger(1)), "version" / construct.Bytewise(construct.BytesInteger(1))))
frame_v1 = construct.Bitwise(construct.Struct("secondary_header" / construct.Struct("duration" / construct.Bytewise(construct.BytesInteger(2)), "data_length" / construct.Bytewise(construct.BytesInteger(2))), "tlc_states" / construct.Array(construct.this.secondary_header.data_length // 24, construct.Struct("state" / construct.Array(16, construct.BitsInteger(12))))))
frame = construct.Bitwise(construct.Struct("primary_header" / construct.Struct("type" / construct.Bytewise(construct.BytesInteger(1)), "version" / construct.Bytewise(construct.BytesInteger(1))), "frame" / construct.Switch(construct.this.primary_header.version, {1: construct.Struct("secondary_header" / construct.Struct("duration" / construct.Bytewise(construct.BytesInteger(2)), "data_length" / construct.Bytewise(construct.BytesInteger(2))), "tlc_states" / construct.Array(construct.this.secondary_header.data_length // 24, construct.Struct("state" / construct.Array(16, construct.BitsInteger(12)))))})))
animation_v1 = construct.Bitwise(construct.Struct("secondary_header" / construct.Struct("name" / construct.Bytewise(construct.PaddedString(32, 'utf8')), "time" / construct.Bytewise(construct.BytesInteger(8)), "crc" / construct.Bytewise(construct.BytesInteger(4)), "tlc_count" / construct.Bytewise(construct.BytesInteger(1)), "frame_count" / construct.Bytewise(construct.BytesInteger(4)), "data_length" / construct.Bytewise(construct.BytesInteger(4))), "frames" / construct.Array(construct.this.secondary_header.frame_count, construct.Struct("primary_header" / construct.Struct("type" / construct.Bytewise(construct.BytesInteger(1)), "version" / construct.Bytewise(construct.BytesInteger(1))), "frame" / construct.Switch(construct.this.primary_header.version, {1: construct.Struct("secondary_header" / construct.Struct("duration" / construct.Bytewise(construct.BytesInteger(2)), "data_length" / construct.Bytewise(construct.BytesInteger(2))), "tlc_states" / construct.Array(construct.this.secondary_header.data_length // 24, construct.Struct("state" / construct.Array(16, construct.BitsInteger(12)))))})))))
animation = construct.Bitwise(construct.Struct("primary_header" / construct.Struct("type" / construct.Bytewise(construct.BytesInteger(1)), "version" / construct.Bytewise(construct.BytesInteger(1))), "animation" / construct.Switch(construct.this.primary_header.version, {1: construct.Struct("secondary_header" / construct.Struct("name" / construct.Bytewise(construct.PaddedString(32, 'utf8')), "time" / construct.Bytewise(construct.BytesInteger(8)), "crc" / construct.Bytewise(construct.BytesInteger(4)), "tlc_count" / construct.Bytewise(construct.BytesInteger(1)), "frame_count" / construct.Bytewise(construct.BytesInteger(4)), "data_length" / construct.Bytewise(construct.BytesInteger(4))), "frames" / construct.Array(construct.this.secondary_header.frame_count, construct.Struct("primary_header" / construct.Struct("type" / construct.Bytewise(construct.BytesInteger(1)), "version" / construct.Bytewise(construct.BytesInteger(1))), "frame" / construct.Switch(construct.this.primary_header.version, {1: construct.Struct("secondary_header" / construct.Struct("duration" / construct.Bytewise(construct.BytesInteger(2)), "data_length" / construct.Bytewise(construct.BytesInteger(2))), "tlc_states" / construct.Array(construct.this.secondary_header.data_length // 24, construct.Struct("state" / construct.Array(16, construct.BitsInteger(12)))))}))))})))