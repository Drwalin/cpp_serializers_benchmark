//MIT License
//
//Copyright (c) 2023 Marek Zalewski
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#define BITSCPP_BYTE_WRITER_V2_NAME_SUFFIX _Buffer
#define BITSCPP_BYTE_WRITER_V2_BT_TYPE Buffer

#include "buffer.hpp"

#include "../testing_core/testing/test.h"

#include "../bitscpp_src/include/bitscpp/ByteReader_v2.hpp"
#include "../bitscpp_src/include/bitscpp/ByteWriter_v2.hpp"
// #include "../bitscpp_src/src/ByteReader_v2.cpp"
// #include "../bitscpp_src/src/ByteWriter_v2.cpp"

#define ByteWriter															 \
	BITSCPP_CONCATENATE_NAMES(ByteWriter, BITSCPP_BYTE_WRITER_V2_NAME_SUFFIX)

namespace MyTypes {
constexpr void serialize(auto &s, MyTypes::Color& v) {
	s.op((uint8_t&)v);
}
constexpr void serialize(auto& s, MyTypes::Vec3& v) {
	s.op_float(v.x);
	s.op_float(v.y);
	s.op_float(v.z);
}
constexpr void serialize(auto& s, MyTypes::Weapon& v) {
	s.op_sized_string(v.name);
	s.op(v.damage);
}
constexpr void serialize(auto& s, MyTypes::Monster& v) {
	s.op(v.pos);
	s.op(v.mana);
	s.op(v.hp);
	s.op_sized_string(v.name);
	s.op_byte_array(v.inventory);
	s.op(v.color);
	s.op(v.weapons);
	s.op(v.equipped);
	s.op(v.path);
}
}

class bitscppArchiver : public ISerializerTest {
public:
	bitscppArchiver() {
		_buf.reserve(1000000);
	}
	virtual ~bitscppArchiver() {}

	Buf serialize(const std::vector<MyTypes::Monster> &data) override {
		_buf.clear();
		{
			bitscpp::v2::ByteWriter writer(_buf);
			writer.op(data);
		}
		
		return Buf{reinterpret_cast<uint8_t *>(_buf.data()), _buf.size()};
	}

	void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {
		bitscpp::v2::ByteReader reader(buf.ptr, buf.bytesCount);
		reader.op(res);
	}

	TestInfo testInfo() const override {
		return {
			SerializationLibrary::BITSCPP,
			"v2",
			""
		};
	}

private:
	Buffer _buf;
};

int main() {
	bitscppArchiver test{};
	return runTest(test);
}
