To embed the single header file into your own project or library, copy the header into your own src code and change the prefix of the lib:
```bash
python3 tools/change_prefix.py \
  --inf include/cdk_error.h \
  --out example/headeronly/my_error.h \
  --old cdk --new my
```

By default, the library has the errno mechanism enabled, so you will need two definitions for errno: `my_errno` and `my_hidden_errno`. You can find those in `example/headeronly/my_error.c`. For more info about how the library is used check out `example.c`.

Compile the example:
```bash
gcc -o build/example_header -Iexample/headeronly example/headeronly/example.c example/headeronly/my_error.c
```

Run the example:
```bash
./build/example_header
```

