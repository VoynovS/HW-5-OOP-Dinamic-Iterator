#include <iostream>
#include <cstddef>
#include <new>
#include <vector>

using namespace std;

class DinamicArr
{
public:
	DinamicArr() { //creates an empty array
		arr_size = 0; //array size
		arr_capacity = 0; //array capacity
		arr_data = nullptr; //pointer to a memory area
	};

	DinamicArr(int size, int* data)
	{
		arr_size = size;
		arr_capacity = size;
		arr_data = new int[size];
		for (int i = 0; i < size; i++)
			arr_data[i] = data[i];
	}

	DinamicArr(const DinamicArr& other) //Creates a copy of an existing array
	{
		arr_size = other.arr_size;
		arr_capacity = arr_size;
		arr_data = nullptr;
		if (arr_size != 0) {
			arr_data = new int[arr_size];
		}
		else {
			arr_data = 0;

			for (int i = 0; i < arr_size; ++i)
				arr_data[i] = other.arr_data[i];
		}
	}
	DinamicArr(int size) //Creates an array of the specified size
	{
		arr_size = size;
		arr_capacity = size;
		if (size != 0) {
			arr_data = new int[size];
		}
		else {
			arr_data = 0;
		}
	}
	~DinamicArr() {//Destructor
		if (arr_data != nullptr)
			delete[] arr_data;
	};

	void resize(int size) //Changing the length of the array
	{
		if (size > arr_capacity) {
			int new_capacity = max(size, arr_size * 2);
			int* new_data = new int[new_capacity];
			for (int i = 0; i < arr_size; ++i)
				new_data[i] = arr_data[i];
			delete[] arr_data;
			arr_data = new_data;
			arr_capacity = new_capacity;
		}
		arr_size = size;
	}

	void clear() {
		delete[] arr_data;
		arr_size = 0;
	}

	void push_back(int val) {
		resize(arr_size + 1);
		arr_data[arr_size - 1] = val;
	}

	void reserve(int val) {
		arr_size = this->arr_size;
		int* tmp = new int[arr_size];
		for (size_t i = 0; i < arr_size; i++) {
			tmp[i] = arr_data[i];
		}
		delete[]arr_data;
		arr_capacity = arr_size + val;
		arr_size = arr_capacity;
		arr_data = new int[arr_capacity] {};
		for (size_t i = 0; i < arr_capacity - val; i++) {
			arr_data[i] = tmp[i];
		}
		delete[]tmp;
	}

	void swap(DinamicArr& other, DinamicArr& other2) {
		DinamicArr tmp;
		tmp = other;
		other = other2;
		other2 = tmp;
	}

	void printArr()const {
		for (int i = 0; i < arr_size; i++) {
			cout << arr_data[i] << ", ";
		}
		cout << "\b.\n";
	}

	void shrink_to_fit() {
		int* tmp = new int[arr_size];
		for (size_t i = 0; i < arr_size; i++) {
			tmp[i] = arr_data[i];
		}
		arr_capacity = arr_size;
		delete[]arr_data;
		arr_data = new int[arr_capacity];
		for (size_t i = 0; i < arr_capacity; i++) {
			arr_data[i] = tmp[i];
		}
		delete[]tmp;
	}

	void pop_back() {
		int* tmp = new int[arr_size];
		for (size_t i = 0; i < arr_size; i++) {
			tmp[i] = arr_data[i];
		}
		delete[]arr_data;
		arr_size -= 1;
		arr_data = new int [arr_size] {};
		for (size_t i = 0; i < arr_size; i++) {
			arr_data[i] = tmp[i];
		}
		delete[]tmp;
	}

	void erase(int begin, int end) {
		int count = 0;
		int* tmp = new int[arr_size];
		for (size_t i = 0; i < arr_size; i++) {
			tmp[i] = arr_data[i];
		}
		delete[]arr_data;
		arr_data = new int[arr_size - (end - begin)];
		for (size_t i = 0; i < arr_size; i++) {
			if (i >= begin && i <= end) {
				count++;
				continue;
			}
			arr_data[i - count] = tmp[i];
		}
		arr_size -= (end - begin + 1);
	}

	void insert(int ind, int val, int count) {
		if (arr_capacity < arr_size + count) {
			reserve(count);
		}
		arr_size += count;
		int* tmp = new int[arr_size];
		for (size_t i = 0; i < ind; i++) {
			tmp[i] = arr_data[i];
		}
		for (size_t i = ind; i < ind + count; i++) {
			tmp[i] = val;
		}
		for (size_t i = ind + count; i < arr_size; i++) {
			tmp[i] = arr_data[i - count];
		}
		delete[]arr_data;
		arr_data = new int[arr_capacity];
		for (int i = 0; i < arr_size; i++) {
			arr_data[i] = tmp[i];
		}
		delete[]tmp;
	}

	void emplace_back(int val) {
		int* tmp = new int[arr_size + 1];
		for (size_t i = 0; i < arr_size; i++) {
			tmp[i] = arr_data[i];
		}
		arr_size += 1;
		for (size_t i = 0; i < arr_size - 1; i++) {
			arr_data[i] = tmp[i];
		}
		arr_data[arr_size - 1] = val;
		delete[]tmp;
	}

	const int* data() const {
		return arr_data;
	}

	int capacity()const {
		return arr_capacity;
	}

	int size() const {
		return arr_size;
	}

	int at(int i) {
		return arr_data[i];
	}

	int front() const {
		return arr_data[0];
	}

	int back() const {
		return arr_data[arr_size - 1];
	}

	/*int capacity() const {
		return arr_capacity;
	}*/

	bool empty() {
		if (arr_capacity > 0) {
			return false;
		}
		else {
			return true;
		}
	}

	bool operator == (const DinamicArr&& other) {
		if (this->arr_size != other.arr_size) {
			return false;
		}
		if (arr_size == other.arr_size) {
			for (size_t i = 0; i < arr_size; i++) {
				if (arr_data[i] != other.arr_data[i]) {
					return false;
				}
				return true;
			}
		}
	}
	DinamicArr& operator =(const DinamicArr& other) {
		arr_size = other.arr_size;
		if (arr_data != nullptr) {
			delete[]arr_data;
		}
		arr_data = new int[other.arr_size]{};
		for (size_t i = 0; i < arr_size; i++) {
			arr_data[i] = other.arr_data[i];
		}
		return *this;
	}

	int& operator [] (int i) {
		return arr_data[i];
	}



private:
	int arr_size{ 0 };
	int arr_capacity{ 0 };
	int* arr_data = nullptr;
	class iterator {
	public:
		int* operator->()const {
			return location_;
		}
		int& operator*()const {
			return *location_;
		};
		operator int* ()const {
			return location_;
		}
		iterator& operator+(int i)const {
			iterator result(*this);
			result.location_ += i;
			return result;
		}
		iterator& operator+=(int i) {
			location_ += i;
			return *this;
		}
		iterator& operator-(int i)const {
			iterator result(*this);
			result.location_ -= i;
			return result;
		}
		iterator& operator-=(int i) {
			location_ -= i;
			return *this;
		}
		iterator& operator--() {
			location_ -= 1;
			return *this;
		}
		iterator& operator--(int) {
			iterator tmp{ *this };
			location_ -= 1;
			return tmp;
		}
		iterator& operator++() {
			location_ += 1;
			return *this;
		}
		iterator& operator++(int) {
			iterator tmp{ *this };
			location_ += 1;
			return tmp;
		}
		operator bool()const {
			return static_cast<bool>(location_);
		}
		bool operator==(const iterator&& other)const {
			return location_ == other.location_;
		}		
		bool operator<(const iterator&& other)const {
			return location_ < other.location_;
		}
		bool operator<=(const iterator&& other)const {
			return location_ <= other.location_;
		}
		bool operator>(const iterator&& other)const {
			return location_ > other.location_;
		}
		bool operator>=(const iterator&& other)const {
			return location_ >= other.location_;
		}
		int& operator[](int i)const {
			return location_[i];
		}
		const DinamicArr const* from()const {
			return &collection_;
		}
	private:
		iterator() = delete;
		iterator(const DinamicArr&& position, int* place) :collection_(position), location_(place) {}
		friend class DinamicArr;
		const DinamicArr& collection_;
		int* location_;
	};
};




int main() {

	return 0;
}
