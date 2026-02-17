# CPP serializers benchmark

### tested libraries
* [bitsery](https://github.com/fraillt/bitsery) 5.2.1
* [boost](https://www.boost.org/) 1.77.0
* [cereal](https://uscilab.github.io/cereal/) 1.3.0
* [flatbuffers](https://google.github.io/flatbuffers/) 2.0.0
* [yas](https://github.com/niXman/yas) 7.1.0
* [protobuf](https://developers.google.com/protocol-buffers/) 3.17.3
* [zpp_bits](https://github.com/eyalz800/zpp_bits) 2.0
* [msgpack](https://github.com/msgpack/msgpack-c) 3.3.0
* [bitscpp](https://github.com/Drwalin/bitscpp) 3.3.0

## GCC 15.2.1 (Arch Linux x86\_64 6.18.6)

Tested with 300000 iterations and 50 objects.

| library     | test case                                                  | bin size | data size | ser time | des time |
| ----------- | ---------------------------------------------------------- | -------- | --------- | -------- | -------- |
| bitscpp     | compressed_float                                           | 49304B   | 4666B     | 730ms    | 1466ms   |
| bitscpp     | compressed_float unsafe_read                               | 49304B   | 4666B     | 730ms    | 1297ms   |
| bitscpp     | general unsafe_read                                        | 49200B   | 7366B     | 686ms    | 1219ms   |
| bitscpp     | general                                                    | 49280B   | 7366B     | 679ms    | 710ms    |
| bitscpp     | v2                                                         | 50088B   | 8078B     | 1496ms   | 1392ms   |
| bitsery     | general                                                    | 100904B  | 6913B     | 1150ms   | 1035ms   |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 101032B  | 6913B     | 1130ms   | 1923ms   |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 96816B   | 7113B     | 1298ms   | 1113ms   |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 113744B  | 4213B     | 1342ms   | 1149ms   |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | 50440B   | 6913B     | 873ms    | 1074ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 60264B   | 6913B     | 1186ms   | 4944ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 91992B   | 6913B     | 1163ms   | 511ms    |
| cereal      | general                                                    | 83696B   | 10413B    | 6906ms   | 5897ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | 40656B   | 10413B    | 797ms    | 805ms    |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | 40664B   | 10413B    | 797ms    | 537ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 54944B   | 8413B     | 8482ms   | 9418ms   |
| yas         | general[<sup>10</sup>](#additional-tests-information)      | 69904B   | 10463B    | 2095ms   | 1320ms   |
| yas         | compression[<sup>11</sup>](#additional-tests-information)  | 74336B   | 7315B     | 2380ms   | 1499ms   |
| yas         | stream[<sup>12</sup>](#additional-tests-information)       | 56608B   | 10463B    | 8371ms   | 8085ms   |
| msgpack     | general                                                    | 85224B   | 8857B     | 1233ms   | 7770ms   |
| zpp_bits    | general                                                    | 48880B   | 8413B     | 644ms    | 605ms    |
| zpp_bits    | fixed buffer                                               | 40704B   | 8413B     | 538ms    | 589ms    |

## Clang 21.1.6 (Arch Linux x86\_64 6.18.6)

Tested with 300000 iterations and 50 objects.

| library     | test case                                                  | bin size | data size | ser time | des time |
| ----------- | ---------------------------------------------------------- | -------- | --------- | -------- | -------- |
| bitscpp     | compressed_float                                           | 42120B   | 4666B     | 824ms    | 1543ms   |
| bitscpp     | compressed_float unsafe_read                               | 46216B   | 4666B     | 775ms    | 1394ms   |
| bitscpp     | general unsafe_read                                        | 37944B   | 7366B     | 778ms    | 1358ms   |
| bitscpp     | general                                                    | 50448B   | 7366B     | 798ms    | 929ms    |
| bitscpp     | v2                                                         | 52088B   | 8078B     | 1946ms   | 1663ms   |
| bitsery     | general                                                    | 53096B   | 6913B     | 1359ms   | 1182ms   |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 58536B   | 6913B     | 1544ms   | 1147ms   |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 57792B   | 7113B     | 1422ms   | 1235ms   |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 58664B   | 4213B     | 2889ms   | 1837ms   |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | 52352B   | 6913B     | 772ms    | 1141ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 53776B   | 6913B     | 1426ms   | 5149ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 53144B   | 6913B     | 1315ms   | 927ms    |
| cereal      | general                                                    | 61264B   | 10413B    | 7919ms   | 6989ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | 42112B   | 10413B    | 799ms    | 756ms    |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | 42120B   | 10413B    | 799ms    | 582ms    |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 47800B   | 8413B     | 8009ms   | 9888ms   |
| yas         | general[<sup>10</sup>](#additional-tests-information)      | 55024B   | 10463B    | 2085ms   | 1445ms   |
| yas         | compression[<sup>11</sup>](#additional-tests-information)  | 59648B   | 7315B     | 2583ms   | 1981ms   |
| yas         | stream[<sup>12</sup>](#additional-tests-information)       | 54016B   | 10463B    | 7656ms   | 8289ms   |
| msgpack     | general                                                    | 80496B   | 8857B     | 3014ms   | 9828ms   |
| zpp_bits    | general                                                    | 42136B   | 8413B     | 585ms    | 727ms    |
| zpp_bits    | fixed buffer                                               | 42152B   | 8413B     | 556ms    | 703ms    |

### Additional tests information

1. deserialization using `brief\_syntax`, similar to `cereal`
2. forward\/backward compatibility enabled for `Monster`
3. all components of Vec3 is compressed in \[-1.0, 1.0\] range with precision 0.01
4. use non-resizable buffer uint8\_t\[150000\] for serialization
5. use stream input\/output adapter, underlying type is std::stringstream
6. on deserialization do not check for errors
7. check buffer size on reading, but writing buffer is preallocated std::array&lt;uint8\_t, 1000000&gt;
8. doesn't check for buffer size when reading, buffer: std::array&lt;uint8\_t, 1000000&gt;
9. use std::stringstream's internal std::string
10. use arena allocator
11. use yas::mem\_&lt;io&gt;stream as buffer
12. with yas::no\_header and yas::compacted
13. using std::stringstream

NOTE: tests for protobuf and flatbuffers is not 100% fair, because huge amount of CPU cycles goes to converting from generated types, to our defined types.

## Why another cpp serializers benchmark

I'm aware that [cpp-serializers](https://github.com/thekvs/cpp-serializers) project already exists, but it's testing set is way too simple and you cannot compile each project to separate executable.

This project contains more realisting data that needs to be serialized.
```cpp
    enum Color : uint8_t {
        Red,
        Green,
        Blue
    };

    struct Vec3 {
        float x;
        float y;
        float z;
    };

    struct Weapon {
        std::string name;
        int16_t damage;
    };

    struct Monster {
        Vec3 pos;
        int16_t mana;
        int16_t hp;
        std::string name;
        std::vector<uint8_t> inventory;
        Color color;
        std::vector<Weapon> weapons;
        Weapon equipped;
        std::vector<Vec3> path;
    };
```

All data is random generated, although seed is hard-coded to get predictable results when running same test multiple times.

All projects implement same interface for serialization and deserialization.
```cpp
struct Buf {
    const uint8_t* ptr;
    size_t bytesCount;
};

class ISerializerTest {
public:
    virtual Buf serialize(const std::vector<MyTypes::Monster>& data) = 0;
    virtual void deserialize(Buf buf, std::vector<MyTypes::Monster>& res) = 0;
    virtual ~ISerializerTest() = default;
};
```

Testing routine consist of few steps:
* data generation step, in which monsters are generated (default 50 monsters)
* warmup step, in which serialization and deserialization is run 5 times, to warmup cpu cache and check if deserialized data equals to original data.
* measurement step, runs serialization and deserialization multiple times (default 300000 samples),
  deserialization happens on same object, to avoid costly allocate operations for new object construction each time.

## Building & testing

1. Build project
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```
2. Run tests with `ctest -VV` **OR**
3. Generate testing results *(requires nodejs)*
    ```bash
    cd ../tools/
    npm install
    npm start
    ```
