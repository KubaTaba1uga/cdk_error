We will install library to `/opt/cdk_error` and use it from there:
```bash
sudo mkdir /opt/cdk_error
sudo chmod 777 /opt/cdk_error
```

Compile and install cdk error as library:
```bash
meson setup --prefix=/opt/cdk_error build
meson compile -C build
meson install -C build
```

Compile the example:
```bash
export PKG_CONFIG_PATH=/opt/cdk_errno/lib/x86_64-linux-gnu/pkgconfig/:$PKG_CONFIG_PATH
gcc -o build/example_lib `pkg-config --cflags cdk_error` new_examples/library/example.c `pkg-config --libs cdk_error`
```

Run the example:
```bash
export LD_LIBRARY_PATH=/opt/cdk_errno/lib/x86_64-linux-gnu/:$LD_LIBRARY_PATH
./build/example_lib
```
