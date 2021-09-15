#pragma once
#include <iostream>
template <typename T>
struct node
{
	node<T>* before;
	T data;
	node<T>* next;
	node<T>()
	{
		before = nullptr;
		data = NULL;
		next = nullptr;
	}
	node<T>(T datanew)
	{
		before = nullptr;
		data = datanew;
		next = nullptr;
	}
	node<T>(node<T>* left)
	{
		this = left;
	}
};
template <typename T>
class ItteratorL
{
private:
	node<T>* abc;
public:
	ItteratorL<T>()
	{
		abc = nullptr;
	}
	ItteratorL<T>(node<T>* left)
	{
		this->abc = left;
	}
	ItteratorL<T>& operator=( ItteratorL<T>& right)
	{
		this->abc = right.abc;
		return *this;
	}
	ItteratorL<T>& operator=( ItteratorL<T>&& right)
	{
		this->abc = right.abc;
		right.abc = nullptr;
		return *this;
	}
	ItteratorL<T>& operator++()
	{
		this->abc = this->abc->next;
		return *this;
	}
	ItteratorL<T>& operator++(int)
	{
		ItteratorL<T> copy(*this);
		this->abc = this->abc->next;
		return copy;
	}
	ItteratorL<T>& operator--()
	{
		this->abc = this->abc->before;
		return *this;
	}
	ItteratorL<T>& operator--(int)
	{
		ItteratorL<T> copy(*this);
		this->abc = this->abc->before;
		return copy;
	}
	T& operator*()
	{
		return this->abc->data;
	}
	node<T>* operator&()
	{
		return this->abc;
	}
	bool operator==(ItteratorL<T> right)
	{
		return (this->abc == right.abc);
	}
	bool operator!=(ItteratorL<T> right)
	{
		return (this->abc != right.abc);
	}
	bool operator<=(ItteratorL<T> right)
	{
		return (this->abc <= right.abc);
	}
	bool operator>=(ItteratorL<T> right)
	{
		return (this->abc >= right.abc);
	}
	bool operator<(ItteratorL<T> right)
	{
		return (this->abc < right.abc);
	}
	bool operator>(ItteratorL<T> right)
	{
		return (this->abc > right.abc);
	}
};
template <typename T>
ItteratorL<T> operator+(ItteratorL<T>& left, int right)
{
	ItteratorL<T> copy(left);
	for (int i = 0; i < right; i++)
	{
		copy++;
	}
	return copy;
}
template <typename T>
ItteratorL<T> operator+=(ItteratorL<T>& left, int right)
{
	for (int i = 0; i < right; i++)
	{
		left++;
	}
	return left;
}
template <typename T>
class List
{
private:
	node<T>* flag;
	int size;
public:
	List<T>()
	{
		flag = nullptr;
		size = NULL;
	}
	List<T>(node<T>* newflag, int newsize)
	{
		if (newflag)
		{
			size = newsize;
			while (newflag->before)
			{
				newflag = newflag->before;
			}
			flag = new node<T>;
			flag->before = nullptr;
			flag->data = newflag->data;
			newflag = newflag->next;
			while (newflag)
			{	
				flag->next = new node<T>;
				flag->next->before = flag;
				flag = flag->next;
				flag->data = newflag->data;
				newflag = newflag->next;
			}
			flag->next = nullptr;
			while (flag->before)
			{
				flag = flag->before;
			}
		}
		
	}
	List<T>(List<T>& abc)
	{
		if (abc->size > 0)
		{
			if (abc->flag)
			{
				this->flag = new node<T>;
				this->size = abc->size;
				while (abc->flag->prev)
				{
					abc->flag = abc->flag->before;
				}
				flag = new node<T>;
				flag->prev = nullptr;
				flag->data = abc->flag->data;
				abc->flag = abc->flag->next;
				while (abc->flag)
				{
					flag->next = new node<T>;
					flag = flag->next;
					flag->before = flag;
					flag->data = abc->flag->data;
					abc->flag = abc->flag->next;
				}
				flag->next = nullptr;
				while (flag->prev)
				{
					flag = flag->before;
				}
			}
		}
	}
	List<T>(List<T>&& abc)
	{
		this->flag = abc->flag;
		this->size = abc->size;
		abc->size = NULL;
		abc->flag = nullptr;
	}
	~List<T>()
	{
		if (flag)
		{
			while (this->flag->before)
			{
				this->flag = this->flag->before;
			}
			for (int i = 0; i < size - 1; i++)
			{
				this->flag = this->flag->next;
				delete this->flag->before;
				if (i == size - 2)
				{
					delete this->flag;
				}
			}
			this->size = NULL;
		}
	}
	List<T>& operator= (List<T>& abc)
	{
		if (abc.size > 0)
		{
			if (abc.flag)
			{
				flag = new node<T>;
				size = abc.size;
				while (abc.flag->before)
				{
					abc.flag = abc.flag->before;
				}
				flag->before = nullptr;
				flag->data = abc.flag->data;
				abc.flag = abc.flag->next;
				while (abc.flag->next)
				{
					flag->next = new node<T>;
					flag->next->before = flag;
					flag = flag->next;
					flag->data = abc.flag->data;
					abc.flag = abc.flag->next;
				}

				flag->next = nullptr;
				while (flag->before)
				{
					flag = flag->before;
				}
			}
		}
		return *this;
	}
	List<T>& operator= (const List<T>&& abc)
	{
		this.flag = abc.flag;
		this.size = abc.size;
		abc.size = NULL;
		abc.flag = nullptr;
		return *this;
	}
	T& front()
	{
		while (this->flag->before)
		{
			this->flag = this->flag->before;
		}
		return this->flag->data;
	}
	T& back()
	{
		while (this->flag->next)
		{
			this->flag = this->flag->next;
		}
		return this->flag->data;
	}
	bool empty()
	{
		return !this->size;
	}
	int getsize()
	{
		return this->size;
	}
	ItteratorL<T> begin()
	{
		while (this->flag->before)
		{
			this->flag = this->flag->before;
		}
		ItteratorL<T> copy(this->flag);
			return copy;
	}
	ItteratorL<T> end()
	{
		while (this->flag->next)
		{
			this->flag = this->flag->next;
		}
		ItteratorL<T> copy(this->flag);
			return copy;
	}
	void clear()
	{
		while (this->flag->before)
		{
			this->flag = this->flag->before;
		}
		for (int i = 0; i < size; i++)
		{
			delete this->flag;
			this->flag = this->flag->next;
		}
		this->size = NULL;
	}
	ItteratorL<T> insert(T* newdt, ItteratorL<T>& pos)
	{
		if (!(this->size))
		{
			this->flag = new node<T>;
			this->flag->before = nullptr;
			this->flag->next= nullptr;
			this->flag->data = newdt;
			pos = begin();
			return pos;
		}
		else
		{
			if (this->size == 1)
			{
				if (pos == begin())
				{
					this->flag->before = new node<T>(newdt);
					flag->before->next = flag;
					flag = flag->before;
					pos = ++begin();
				}
				else
				{
					this->flag->next = new node<T>(newdt);
					flag->next->before = flag;
					pos = end();
				}
				return pos;
			}
			if (pos == end())
			{
				while (flag->next)
				{
					flag = flag->next;
				}
				this->flag->next = new node<T>(newdt);
				flag->next->before = flag;
				return end();
			}
			while (flag->before)
			{
				flag = flag->before;
			}
			flag = &pos;
			if (flag->before)
			{
				this->flag->before->next = new node<T>(newdt);
				flag->before->next->before = flag->before;
				flag->before = flag->before->next;
				flag->before->next = flag;
				return pos; // сломаются
			}
			else
			{
				this->flag->before = new node<T>(newdt);
				flag->before->next = flag;
				flag = flag->before;
				pos = ++begin();
				return pos; // сломаются
			}
		}
	}
	ItteratorL<T> erase(ItteratorL<T>& pos)
	{
		if (empty())
		{
			throw "empty list";
		}
		flag = &pos;
		if (this->size == 1)
		{
			delete flag;
			flag = nullptr;
			this->size--;
			return end();
		}
		if (pos == begin())
		{
			flag = flag->next;
			delete flag->before;
			flag->before = nullptr;
			this->size--;
			return begin();
		}
		if (pos == end())
		{
			flag = flag->before;
			delete flag->next;
			flag->next = nullptr;
			this->size--;
			return end();
		}
		while (flag->before)
		{
			flag = flag->before;
		}
		int count = 0;
		while (flag != &pos)
		{
			count++;
			flag = flag->next;
		}
		flag->before->next = flag->next;
		flag->next->before = flag->before;
		delete flag;
		pos = begin() + count;
		return pos;
	}
};
	template <typename T>
	bool operator== (List<T>& left, List<T>& right)
	{
		if (left.getsize() == right.getsize())
		{
			ItteratorL<T> rightbegin = right.begin();
			ItteratorL<T> leftbegin = left.begin();
			while (leftbegin == left.end())
			{
				if (*leftbegin != *rightbegin)
				{
					return false;
				}
				++leftbegin;
				++rightbegin;
			}
			return true;
		}
		return false;
	}
	template <typename T>
	bool operator!= (List<T>& left, List<T>& right)
	{
		return !(left == right);
	}
	template <typename T>
	bool operator<= (List<T>& left, List<T>& right)
	{
		if (left.getsize() == right.getsize())
		{
			ItteratorL<T> rightbegin = right.begin();
			ItteratorL<T> leftbegin = left.begin();
			while (leftbegin != left.end())
			{
				if (*leftbegin > *rightbegin)
				{
					return false;
				}
				++leftbegin;
				++rightbegin;
			}
			return true;
		}
		return (left.getsize() <= right.getsize());
	}
	template <typename T>
	bool operator>= (List<T>& left, List<T>& right)
	{
		if (left.getsize() == right.getsize())
		{
			ItteratorL<T> rightbegin = right.begin();
			ItteratorL<T> leftbegin = left.begin();
			while (leftbegin != left.end())
			{
				if (*leftbegin < *rightbegin)
				{
					return false;
				}
				++leftbegin;
				++rightbegin;
			}
			return true;
		}
		return (left.getsize() >= right.getsize());
	}
	template <typename T>
	bool operator< (List<T>& left, List<T>& right)
	{
		return !(left >= right);
	}
	template <typename T>
	bool operator> (List<T>& left, List<T>& right)
	{
		return !(left <= right);
	}

