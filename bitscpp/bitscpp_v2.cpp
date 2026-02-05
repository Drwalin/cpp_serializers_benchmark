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

#include "../bitscpp_src/include/bitscpp/ByteReader_v2.hpp"
#include "../bitscpp_src/include/bitscpp/ByteWriter_v2.hpp"
#include "../testing_core/testing/test.h"

#include "../bitscpp_src/src/ByteWriter_v2.cpp"

#define ByteWriter                                                             \
	BITSCPP_CONCATENATE_NAMES(ByteWriter, BITSCPP_BYTE_WRITER_V2_NAME_SUFFIX)

namespace bitscpp {
template<>
	inline bitscpp::v2::ByteWriter& _impl_v2_writer<MyTypes::Color>::op(bitscpp::v2::ByteWriter& s, const MyTypes::Color& v) {
		s.op((uint8_t&)v);
		return s;
	}
template<>
	inline bitscpp::v2::ByteWriter& _impl_v2_writer<MyTypes::Vec3>::op(bitscpp::v2::ByteWriter& s, const MyTypes::Vec3& v) {
		s.op_bfloat(v.x);
		s.op_bfloat(v.y);
		s.op_bfloat(v.z);
		return s;
	}
template<>
	inline bitscpp::v2::ByteWriter& _impl_v2_writer<MyTypes::Weapon>::op(bitscpp::v2::ByteWriter& s, const MyTypes::Weapon& v) {
		s.op_sized_string(v.name);
		s.op(v.damage);
		return s;
	}
template<>
	inline bitscpp::v2::ByteWriter& _impl_v2_writer<MyTypes::Monster>::op(bitscpp::v2::ByteWriter& s, const MyTypes::Monster& v) {
		s.op(v.pos);
		s.op_int(v.mana);
		s.op_int(v.hp);
		s.op_sized_string(v.name);
		s.op_byte_array(v.inventory);
		s.op(v.color);
		s.op(v.weapons);
		s.op(v.equipped);
		s.op(v.path);
		return s;
	}
	
	

template<>
	inline bitscpp::v2::ByteReader& _impl_v2_reader<MyTypes::Color>::op(bitscpp::v2::ByteReader& s, MyTypes::Color& v) {
		s.op((uint8_t&)v);
		return s;
	}
template<>
	inline bitscpp::v2::ByteReader& _impl_v2_reader<MyTypes::Vec3>::op(bitscpp::v2::ByteReader& s, MyTypes::Vec3& v) {
		s.op_bfloat(v.x);
		s.op_bfloat(v.y);
		s.op_bfloat(v.z);
		return s;
	}
template<>
	inline bitscpp::v2::ByteReader& _impl_v2_reader<MyTypes::Weapon>::op(bitscpp::v2::ByteReader& s, MyTypes::Weapon& v) {
		s.op_sized_string(v.name);
		s.op(v.damage);
		return s;
	}
template<>
	inline bitscpp::v2::ByteReader& _impl_v2_reader<MyTypes::Monster>::op(bitscpp::v2::ByteReader& s, MyTypes::Monster& v) {
		s.op(v.pos);
		s.op(v.mana);
		s.op(v.hp);
		s.op_sized_string(v.name);
		s.op_byte_array(v.inventory);
		s.op(v.color);
		s.op(v.weapons);
		s.op(v.equipped);
		s.op(v.path);
		return s;
	}
} // namespace bitscpp

class bitscppArchiver : public ISerializerTest {
public:
    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
		_buf.reserve(10000000);
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
            "general",
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
