{
  "targets" : [
    {
      "target_name": "iso8583",
      "sources": [ 
        "src/iso8583.cc", 
        "src/dl_iso8583.c", 
        "src/dl_iso8583_common.c", 
        "src/dl_iso8583_defs_1987.c", 
        "src/dl_iso8583_defs_1993.c", 
        "src/dl_iso8583_fields.c"
      ],
      "include_dirs" : [
        "src",
        "src/common",
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
