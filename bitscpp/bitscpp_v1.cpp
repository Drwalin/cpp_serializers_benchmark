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

#include "../bitscpp_src/include/bitscpp/ByteReader.hpp"
#include "../bitscpp_src/include/bitscpp/ByteWriter.hpp"
#include "../testing_core/testing/test.h"

namespace bitscpp {
	template<typename BT>
	inline bitscpp::ByteWriter<BT>& op(bitscpp::ByteWriter<BT>& s, const MyTypes::Color& v) {
		s.op((uint8_t&)v);
		return s;
	}
	template<typename BT>
	inline bitscpp::ByteWriter<BT>& op(bitscpp::ByteWriter<BT>& s, const MyTypes::Vec3& v) {
		s.op(v.x);
		s.op(v.y);
		s.op(v.z);
		return s;
	}
	template<typename BT>
	inline bitscpp::ByteWriter<BT>& op(bitscpp::ByteWriter<BT>& s, const MyTypes::Weapon& v) {
		s.op_string_sized(v.name, 1);
		s.op(v.damage);
		return s;
	}
	template<typename BT>
	inline bitscpp::ByteWriter<BT>& op(bitscpp::ByteWriter<BT>& s, const MyTypes::Monster& v) {
		s.op(v.pos);
		s.op(v.mana);
		s.op(v.hp);
		s.op_string_sized(v.name, 1);
		s.op(v.inventory);
		s.op(v.color);
		s.op(v.weapons);
		s.op(v.equipped);
		s.op(v.path);
		return s;
	}
	
	
	
	inline bitscpp::ByteReader<true>& op(bitscpp::ByteReader<true>& s, MyTypes::Color& v) {
		s.op((uint8_t&)v);
		return s;
	}
	inline bitscpp::ByteReader<true>& op(bitscpp::ByteReader<true>& s, MyTypes::Vec3& v) {
		s.op(v.x);
		s.op(v.y);
		s.op(v.z);
		return s;
	}
	inline bitscpp::ByteReader<true>& op(bitscpp::ByteReader<true>& s, MyTypes::Weapon& v) {
		s.op_string_sized(v.name, 1);
		s.op(v.damage);
		return s;
	}
	inline bitscpp::ByteReader<true>& op(bitscpp::ByteReader<true>& s, MyTypes::Monster& v) {
		s.op(v.pos);
		s.op(v.mana);
		s.op(v.hp);
		s.op_string_sized(v.name, 1);
		s.op(v.inventory);
		s.op(v.color);
		s.op(v.weapons);
		s.op(v.equipped);
		s.op(v.path);
		return s;
	}
} // namespace bitscpp

#include "buffer.hpp"

class bitscppArchiver : public ISerializerTest {
public:
    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        _buf.clear();
		{
			bitscpp::ByteWriter writer(_buf);
			writer.op(data);
		}
		
        return Buf{reinterpret_cast<uint8_t *>(_buf.data()), _buf.size()};
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {
		bitscpp::ByteReader<true> reader(buf.ptr, buf.bytesCount);
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
