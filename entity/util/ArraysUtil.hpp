// Created by author ethereal on 2024/12/15.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace common::io
{
class ArraysUtil abstract
{
public:
	/// \brief Utility class for operations on arrays.
	/// \details The Arrays class provides static methods for various operations on arrays,
	/// including conversion to a vector, binary search, copying, comparison, filling,
	/// sorting, and converting to a string representation. These methods are designed
	/// to work with raw arrays and require the array size to be specified. The class is
	/// abstract and cannot be instantiated.
	template <typename T> static auto asList(const T* array, size_t size) -> std::vector<T> {
		return std::vector<T>(array, array + size);
	}

	/// \brief Performs a binary search for a key within the specified array.
	/// \details This method searches for a given key within an array using the binary search algorithm.
	/// The array must be sorted in ascending order prior to calling this method.
	/// It returns the index of the key if found, or -1 if the key is not present.
	/// \tparam T The type of elements in the array, supporting comparison operators.
	/// \param array A pointer to the first element of the array to be searched.
	/// \param size The number of elements in the array.
	/// \param key The value to search for within the array.
	/// \returns The index of the key within the array if found; otherwise, -1.
	template <typename T> static auto binarySearch(const T* array, size_t size, const T& key) -> int {
		auto it = std::lower_bound(array, array + size, key);
		if (it != array + size && *it == key) {
			return static_cast<int>(it - array);
		}
		return -1;
	}

	/// \brief Searches for a given key within a range of the array.
	/// \details This method searches for a given key within a range of the array using the binary search algorithm.
	/// The array must be sorted in ascending order prior to calling this method.
	/// It returns the index of the key if found, or -1 if the key is not present.
	/// \tparam T The type of elements in the array, supporting comparison operators.
	/// \param array A pointer to the first element of the array to be searched.
	/// \param fromIndex The index of the first element in the range to be searched.
	/// \param toIndex The index of the last element in the range to be searched.
	/// \param key The value to search for within the array.
	/// \returns The index of the key within the array if found; otherwise, -1.
	template <typename T> static auto binarySearch(const T* array, size_t fromIndex, size_t toIndex, const T& key) -> int {
		if (fromIndex >= toIndex) throw std::out_of_range("Invalid range");
		auto start = array + fromIndex;
		auto end = array + toIndex;
		auto it = std::lower_bound(start, end, key);
		if (it != end && *it == key) {
			return static_cast<int>(it - array);
		}
		return -1;
	}

	/// \brief Creates a copy of the specified original array of elements.
	/// \details This method creates a new vector containing all the elements from the specified original array.
	/// The original array is not changed.
	/// \tparam T The type of elements in the array.
	/// \param original The original array to copy.
	/// \param originalSize The length of the original array.
	/// \param newLength
	/// \returns A new vector containing all the elements from the original array.
	template <typename T> static auto copyOf(const T* original, const size_t originalSize, size_t newLength) -> std::vector<T> {
		std::vector<T> result(newLength);
		size_t copyLength = std::min(originalSize, newLength);
		std::copy(original, original + copyLength, result.begin());
		return result;
	}

	/// \brief Copies a range of elements from an original array into a new vector.
	/// \details This method creates a new vector containing elements from the specified range of the original array.
	/// The range is defined by the indices from and to. If from is greater than to, an exception is thrown.
	/// \tparam T The type of elements in the array.
	/// \param original A pointer to the original array.
	/// \param from The starting index of the range to copy, inclusive.
	/// \param to The ending index of the range to copy, exclusive.
	/// \returns A new vector containing the elements in the specified range from the original array.
	/// \throws std::out_of_range if from is greater than to.
	template <typename T> static auto copyOfRange(const T* original, size_t from, size_t to) -> std::vector<T> {
		if (from > to) throw std::out_of_range("Invalid range");
		return std::vector<T>(original + from, original + to);
	}

	/// \brief Checks if two arrays are equal.
	/// \details This method compares two arrays to determine if they are equal.
	/// The arrays are considered equal if they contain the same elements in the same order.
	/// \tparam T The type of elements in the array.
	/// \param a A pointer to the first array.
	/// \param sizeA The size of the first array.
	/// \param b A pointer to the second array.
	/// \param sizeB The size of the second array.
	/// \returns true if the two arrays are equal; otherwise, false.
	template <typename T> static auto equals(const T* a, size_t sizeA, const T* b, const size_t sizeB) -> bool {
		if (sizeA != sizeB) return false;
		return std::equal(a, a + sizeA, b);
	}

	/// \brief Fills the specified array with the specified element.
	/// \details This method fills the specified array with the specified element.
	/// \tparam T The type of elements in the array.
	/// \param array A pointer to the array to be filled.
	/// \param size The size of the array.
	/// \param value The element to be inserted in the array.
	template <typename T> static auto fill(T* array, size_t size, const T& value) -> void {
		std::fill(array, array + size, value);
	}

	/// \brief Sorts the specified array in ascending order.
	/// \details This method sorts the specified array in ascending order.
	/// It uses the std::sort algorithm to sort the array in-place.
	/// \tparam T The type of elements in the array.
	/// \param array A pointer to the array to be sorted.
	/// \param size The size of the array.
	template <typename T> static auto sort(T* array, size_t size) -> void {
		std::sort(array, array + size);
	}

	/// \brief Sorts a range within the specified array in ascending order.
	/// \details This method sorts a specified range of the array in ascending order.
	/// It uses the std::sort algorithm to sort the array elements in-place from the
	/// specified starting index to the ending index (exclusive).
	/// \tparam T The type of elements in the array.
	/// \param array A pointer to the array to be sorted.
	/// \param fromIndex The index of the first element in the range to be sorted.
	/// \param toIndex The index after the last element in the range to be sorted.
	/// \throws std::out_of_range if the range is invalid (i.e. fromIndex >= toIndex).
	template <typename T> static auto sort(T* array, size_t fromIndex, size_t toIndex) -> void {
		if (fromIndex >= toIndex) throw std::out_of_range("Invalid range");
		std::sort(array + fromIndex, array + toIndex);
	}

	/// \brief Converts the specified array to a string representation.
	/// \details This method generates a string representation of the specified array.
	/// The string representation is a comma-separated list of elements within square brackets.
	/// \tparam T The type of elements in the array.
	/// \param array A pointer to the array to be converted to a string.
	/// \param size The size of the array.
	/// \returns A string representation of the array.
	template <typename T> static auto toString(const T* array, const size_t size) -> std::string {
		std::ostringstream oss;
		oss << "[";
		for (size_t i = 0; i < size; ++i) {
			oss << array[i];
			if (i < size - 1) oss << ", ";
		}
		oss << "]";
		return oss.str();
	}
};
}
