#include <cstdint>
#include <cstdlib>

class Buffer
{
public:
	
	Buffer()
	{
		_capacity = 64;
		_size = 0;
		_data = (uint8_t *)malloc(_capacity);
	}
	~Buffer() {
		free(_data);
		_data = nullptr;
		_size = 0;
		_capacity = 0;
	}
	
	uint8_t *_data;
	size_t _size;
	size_t _capacity;
	
	uint8_t *data() {
		return _data;
	}
	size_t size() {
		return _size;
	}
	size_t capacity() {
		return _capacity;
	}
	void resize(size_t s) {
		reserve(s);
		_size = s;
	}
	void reserve(size_t c) {
		if (_capacity >= c) {
			[[likely]];
			return;
		}
		_capacity = (c*3)/2+32;
		_data = (uint8_t *)realloc(_data, _capacity);
	}
	void clear() {
		_size = 0;
	}
};
