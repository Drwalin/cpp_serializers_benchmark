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

## GCC 13.2.1 (Arch Linux x86\_64 6.8.6)

Tested with 1000000 iterations and 80 objects.

| library     | test case                                                  | bin size | data size | ser time | des time |
| ----------- | ---------------------------------------------------------- | -------- | --------- | -------- | -------- |
| bitscpp     | general                                                    | 48984B   | 11527B    | 3580ms   | 3642ms   |
| bitscpp     | compressed_float                                           | 49144B   | 7324B     | 3809ms   | 4927ms   |
| bitscpp     | compressed_float unsafe_read                               | 49160B   | 7324B     | 3925ms   | 4360ms   |
| bitscpp     | general unsafe_read                                        | 49048B   | 11527B    | 3779ms   | 4522ms   |
| bitsery     | general                                                    | 83800B   | 10804B    | 6448ms   | 4877ms   |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 83928B   | 10804B    | 6447ms   | 4195ms   |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 92512B   | 11124B    | 5212ms   | 4640ms   |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 96312B   | 6601B     | 7528ms   | 5988ms   |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | 50360B   | 10804B    | 4447ms   | 5601ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 59792B   | 10804B    | 6775ms   | 22189ms  |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 83136B   | 10804B    | 6304ms   | 2643ms   |
| cereal      | general                                                    | 82816B   | 16229B    | 31590ms  | 25792ms  |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | 48768B   | 16229B    | 4084ms   | 5419ms   |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | 44672B   | 16229B    | 4188ms   | 2857ms   |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 54592B   | 13129B    | 39496ms  | 49056ms  |
| msgpack     | general                                                    | 85296B   | 13805B    | 5778ms   | 42534ms  |
| yas         | general[<sup>10</sup>](#additional-tests-information)      | 69840B   | 16309B    | 10438ms  | 7139ms   |
| yas         | compression[<sup>11</sup>](#additional-tests-information)  | 74168B   | 11419B    | 12394ms  | 7724ms   |
| yas         | stream[<sup>12</sup>](#additional-tests-information)       | 60280B   | 16309B    | 37138ms  | 37877ms  |
| zpp_bits    | general                                                    | 57088B   | 13129B    | 3118ms   | 3034ms   |
| zpp_bits    | fixed buffer                                               | 44712B   | 13129B    | 2853ms   | 3133ms   |


## Clang 12.0.1 (Ubuntu 20.04 x64)

Tested with 300000 iterations and 50 objects.

| library     | test case                                                  | bin size | data size | ser time | des time |
| ----------- | ---------------------------------------------------------- | -------- | --------- | -------- | -------- |
| bitsery     | general                                                    | 53728B   | 6913B     | 2128ms   | 1832ms   |
| bitsery     | brief syntax[<sup>1</sup>](#additional-tests-information)  | 55320B   | 6913B     | 2789ms   | 2071ms   |
| bitsery     | compatibility[<sup>2</sup>](#additional-tests-information) | 54360B   | 7113B     | 2195ms   | 1953ms   |
| bitsery     | compression[<sup>3</sup>](#additional-tests-information)   | 54688B   | 4213B     | 4315ms   | 4181ms   |
| bitsery     | fixed buffer[<sup>4</sup>](#additional-tests-information)  | 49248B   | 6913B     | 946ms    | 1941ms   |
| bitsery     | stream[<sup>5</sup>](#additional-tests-information)        | 54776B   | 6913B     | 2047ms   | 6089ms   |
| bitsery     | unsafe read[<sup>6</sup>](#additional-tests-information)   | 49688B   | 6913B     | 2092ms   | 1162ms   |
| boost       | general                                                    | 237008B  | 11037B    | 16011ms  | 13017ms  |
| cereal      | general                                                    | 61480B   | 10413B    | 9977ms   | 8565ms   |
| flatbuffers | general                                                    | 62512B   | 14924B    | 9812ms   | 3472ms   |
| handwritten | general[<sup>7</sup>](#additional-tests-information)       | 43112B   | 10413B    | 1391ms   | 1321ms   |
| handwritten | unsafe[<sup>8</sup>](#additional-tests-information)        | 43120B   | 10413B    | 1393ms   | 1212ms   |
| iostream    | general[<sup>9</sup>](#additional-tests-information)       | 48632B   | 8413B     | 10992ms  | 12771ms  |
| msgpack     | general                                                    | 77384B   | 8857B     | 3563ms   | 14705ms  |
| protobuf    | general                                                    | 2032712B | 10018B    | 18125ms  | 20211ms  |
| protobuf    | arena[<sup>10</sup>](#additional-tests-information)        | 2032760B | 10018B    | 9166ms   | 11378ms  |
| yas         | general[<sup>11</sup>](#additional-tests-information)      | 51000B   | 10463B    | 2114ms   | 1558ms   |
| yas         | compression[<sup>12</sup>](#additional-tests-information)  | 51424B   | 7315B     | 2874ms   | 2739ms   |
| yas         | stream[<sup>13</sup>](#additional-tests-information)       | 54680B   | 10463B    | 10624ms  | 10604ms  |
| zpp_bits    | general                                                    | 47128B   | 8413B     | 790ms    | 715ms    |
| zpp_bits    | fixed buffer                                               | 43056B   | 8413B     | 605ms    | 694ms    |

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
