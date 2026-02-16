#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <cstdio>

template <typename T> void swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

class Buffer
{
public:
	Buffer()
	{
		_capacity = 0;
		_size = 0;
		_data = nullptr;
	}
	~Buffer()
	{
		if (_data) {
			free(_data);
		}
		_data = nullptr;
		_size = 0;
		_capacity = 0;
	}

	Buffer(Buffer &&o)
	{
		_data = o._data;
		_size = o._size;
		_capacity = o._capacity;
	}
	Buffer &operator=(Buffer &&o)
	{
		free(_data);
		_data = o._data;
		_size = o._size;
		_capacity = o._capacity;
		o._data = nullptr;
		o._size = 0;
		o._capacity = 0;
		return *this;
	}
	Buffer(Buffer &o) = delete;
	Buffer(const Buffer &o) = delete;
	Buffer &operator=(Buffer &o) = delete;
	Buffer &operator=(const Buffer &o) = delete;

	inline uint8_t *data() { return _data; }
	inline size_t size() const { return _size; }
	inline size_t capacity() const { return _capacity; }
	inline void resize(size_t s)
	{
		reserve(s);
		_size = s;
	}
	inline void reserve(size_t c)
	{
		if (_capacity >= c) {
			[[likely]];
			return;
		}
		_capacity = (c * 3) / 2 + 32;
		_data = (uint8_t *)realloc(_data, _capacity);
	}
	inline void clear() { _size = 0; }
	inline void push_back(uint8_t byte)
	{
		if (_capacity == _size) {
			[[unlikely]];
			reserve(_size + 1);
		}
		_data[_size] = byte;
		_size++;
	}
	inline void write(const uint8_t *data, uint32_t bytes)
	{
		if (_capacity - _size < bytes) {
			[[unlikely]];
			reserve(_size + bytes);
		}
		memcpy(_data + _size, data, bytes);
		_size += bytes;
	}

public:
	uint8_t *_data;
	size_t _size;
	size_t _capacity;
};

namespace std
{
inline void swap(Buffer &a, Buffer &b)
{
	::swap(a._data, b._data);
	::swap(a._size, b._size);
	::swap(a._capacity, b._capacity);
}
} // namespace std
