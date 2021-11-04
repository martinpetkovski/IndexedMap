#pragma once
#include <vector>
#include <unordered_map>
#include <cassert>

#ifndef _NODISCARD
#define _NODISCARD [[nodiscard]]
#endif

template<typename KeyType, typename ValueType>
class IndexedMap
{
private:
	std::unordered_map<KeyType, size_t> mMap;
	std::vector<ValueType> mArray;
public:
	_NODISCARD size_t size() const
	{
		return mArray.size();
	}

	void reserve(size_t maxCount)
	{
		mMap.reserve(maxCount);
		mArray.reserve(maxCount);
	}

	void clear()
	{
		mMap.clear();
		mArray.clear();
	}

	_NODISCARD bool is_empty() const
	{
		return mArray.empty();
	}

	_NODISCARD size_t capacity() const
	{
		return mArray.capacity();
	}

	_NODISCARD ValueType* data()
	{
		return mArray.data();
	}

	_NODISCARD bool exists(const KeyType& key) const
	{
		return mMap.find(key) != mMap.end();
	}

	_NODISCARD bool is_index_valid(size_t index) const
	{
		return index < size();
	}

	bool insert(const KeyType& key, const ValueType& value)
	{
		bool retVal = false;
		const auto& valueIt = mMap.find(key);
 		if (valueIt == mMap.end())
		{
			mArray.emplace_back(value);
			mMap.insert_or_assign(key, mArray.size()-1);
			retVal = true;
		}

		return retVal;
	}

	bool insert_or_assign(const KeyType& key, const ValueType& value)
	{
		bool retVal = false;
		const auto& valueIt = mMap.find(key);
		if (valueIt != mMap.end())
		{
			mArray[valueIt->second] = value;
		}
		else
		{
			assert(insert(key, value)); // insert failed
		}

		return retVal;
	}

	bool remove(const KeyType& key)
	{
		bool retVal = false;
		const auto& valueIt = mMap.find(key);
		if (valueIt != mMap.end())
		{
			for (auto& mapItem : mMap)
			{
				if (mapItem.second > valueIt->second)
					mapItem.second--;
			}

			mArray.erase(std::next(mArray.begin(), valueIt->second));
			mMap.erase(key);
		}

		return retVal;
	}

	_NODISCARD auto begin() noexcept { return mArray.begin();}
	_NODISCARD auto begin() const noexcept { return mArray.begin();}
	_NODISCARD auto end() noexcept { return mArray.end(); }
	_NODISCARD auto end() const noexcept { return mArray.end(); }
	_NODISCARD auto rbegin() noexcept { return mArray.rbegin(); }
	_NODISCARD auto rbegin() const noexcept { return mArray.rbegin(); }
	_NODISCARD auto rend() noexcept { return mArray.rend(); }
	_NODISCARD auto rend() const noexcept { return mArray.rend(); }
	_NODISCARD auto cbegin() const noexcept { return mArray.cbegin(); }
	_NODISCARD auto cend() const noexcept { return mArray.cend(); }
	_NODISCARD auto crbegin() const noexcept { return mArray.crbegin(); }
	_NODISCARD auto crend() const noexcept { return mArray.crend(); }

	_NODISCARD ValueType& get(const KeyType& key)
	{
		auto valueIt = mMap.find(key);
		assert(valueIt != mMap.end()); // trying to access a non-existent item
		
		return mArray[valueIt->second]; 
	}

	_NODISCARD ValueType& get_index(size_t index)
	{
		assert(is_index_valid(index)); // index out of bounds

		return mArray[index];
	}

	_NODISCARD ValueType& operator[](const KeyType& key) noexcept
	{
		return get(key);
	}
};