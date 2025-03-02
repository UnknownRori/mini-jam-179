# Escape Velocity

Escape Velocity is 2d scrolling game about escaping destruction inside a building


## System Requirement

| Component |   Minimum  | Recommended |
|-----------|------------|-------------|
|    CPU    |   2.0 Ghz  |   2.0 Ghz   |
|    RAM    |   200 Mb   |   300 Mb    |
|    GPU    |   512 Mb   |  > 1.0 Gb   |

* The requirement might change over the course of development

## Development

```
git clone https://github.com/UnknownRori/mini-jam-174

cd mini-jam-174

# So it won't take so long :)
git submodule update --init --depth 1

# Generate and run Desktop build
cmake -S . -B build
cmake --build ./build/

# Generate and run Web build
# I know you guys can use emscripten, there is the docs to install it
emcmake cmake -S . -B web-build -DPLATFORM=Web
cmake --build ./web-build

# Or you guys are lazy
make web # For web build  just make sure emscripten already in path and activated
make desktop # For desktop build
```
