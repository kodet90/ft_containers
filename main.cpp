#include <iostream>
#include "input_iterator.hpp"

#ifdef STD // Use std containers
	#include <vector>
	#include <map>
	#include <stack>
    #include <set>
	namespace ft = std;
#else // Use ft containers
	#include "vector.hpp"
	#include "map.hpp"
	#include "stack.hpp"
    #include "set.hpp"
#endif

#define SUBJECT(s) std::cout << std::endl << "====" << s << "====" << std::endl << std::endl
#define HEADER(s) std::cout << std::endl << "----" << s << "----" << std::endl << std::endl
#define PRINT(s) std::cout << s << std::endl
#define VECTOR(v) print_vector(v)
#define IT(i) PRINT(*i)
#define MAP(m) print_map(m)
#define IT_MAP(i) PRINT((i)->first << " => " << (i)->second)
#define STACK(s) print_stack(s)
#define SET(s) print_set(s)
#define IT_SET(i) PRINT(*i)

template <class T>
void print_vector(ft::vector<T> &v)
{
    for (typename ft::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
	    PRINT(*it);
}

template <class Key, class T>
void print_map(ft::map<Key, T> &m)
{
	for (typename ft::map<Key, T>::iterator it = m.begin(); it != m.end(); ++it)
		IT_MAP(it);
}

template <class T, class Container>
void print_stack(ft::stack<T, Container> &s)
{
    ft::stack<T, Container> tmp;
    int n = s.size();
    for (int i = 0; i < n; ++i)
    {
        T t = s.top();
        s.pop();
        tmp.push(t);
        PRINT(t);
    }
    s = tmp;
}

template <class Key>
void print_set(ft::set<Key> &s)
{
    for (typename ft::set<Key>::iterator it = s.begin(); it != s.end(); ++it)
        IT_SET(it);
}

class e_test : public std::exception {
public:
	const char* what() const _NOEXCEPT {return "BAM";}
};

class test {
public:
	explicit test(int i = 0) : f(i), c(g++), n(new int) {++x; std::cout << f << "." << c << "." << *n << ":" << x << " test default constructor " << std::endl;}//this << std::endl;}
	test(const test &t) : f(t.f), c(t.c), n(new int(*t.n + 1)) {++x;
		if (f == 21 && c == 'a' && *n == 3) {
			delete n;
			std::cout << "throw BAM" << std::endl;
			throw e_test();
		}
		std::cout << f << "." << c << "." << *n << ":" << x << " test copy constructor " << std::endl;}//this << std::endl;}
	test &operator=(const test &t) {f = t.f; c = t.c; *n = *t.n + 1; std::cout << f << "." << c << "." << *n << ":" << x << " test assign operator " << std::endl; return *this;}//this << std::endl; return *this;}
	virtual ~test() {g = --x ? g : 'a'; std::cout << f << "." << c << "." << *n << ":" << x << " test destructor " << std::endl; delete n;}//this << std::endl; delete n;}
	friend std::ostream &operator<<(std::ostream &o, const test &test);

private:
	static int x;
	static char g;
	int f;
	char c;
	int *n;
};
std::ostream &operator<<(std::ostream &o, const test &test) {o << test.f << "." << test.c << "." << *test.n; return o;}
int test::x = 0;
char test::g = 'a';


//#define _pair ft::pair
//
//template <typename T>
//std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
//{
////std::cerr << "; " << iterator << std::endl;
//    o << "key: " << iterator->first << " | value: " << iterator->second;
//    if (nl)
//        o << std::endl;
//    return ("");
//}
//
//template <typename T_MAP>
//void	printSize(T_MAP const &mp, bool print_content = 1)
//{
//    std::cout << "size: " << mp.size() << std::endl;
//    std::cout << "max_size: " << mp.max_size() << std::endl;
//    if (print_content)
//    {
//        typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
//        std::cout << std::endl << "Content is:" << std::endl;
//        for (; it != ite; ++it)
//            std::cout << "- " << printPair(it, false) << std::endl;
//    }
//    std::cout << "###############################################" << std::endl;
//}
//
//#define T1 int
//#define T2 std::string
//typedef ft::map<T1, T2>::value_type T3;
//typedef ft::map<T1, T2>::iterator iterator;
//
////static int iter = 0;
//
//template <typename MAP, typename U>
//void	ft_insert(MAP &mp, U param)
//{
//    _pair<iterator, bool> tmp;
//
//    std::cout << "\t-- [" << iter++ << "] --" << std::endl;
//    tmp = mp.insert(param);
////std::cout << "@@ " << tmp.first << std::endl;
//    std::cout << "insert return: " << printPair(tmp.first);
//    std::cout << "Created new node: " << tmp.second << std::endl;
//    printSize(mp);
//}
//
//template <typename MAP, typename U, typename V>
//void	ft_insert(MAP &mp, U param, V param2)
//{
//    iterator tmp;
//
//    std::cout << "\t-- [" << iter++ << "] --" << std::endl;
//    tmp = mp.insert(param, param2);
////std::cout << "@ " << tmp << std::endl;
//    std::cout << "insert return: " << printPair(tmp);
////std::cout << "$ " << std::endl;
//    printSize(mp);
////std::cout << "! " << std::endl;
//}

int main()
{
//    {
//        ft::vector<int, std::allocator<const int> > vec;
//        ft::set<int, std::less<int>, std::allocator<const int> > vec;
//        ft::map<int, int, std::less<int>, std::allocator<ft::pair<const int, int> > > map;
//    }
//    exit(0);
//    {
//        ft::map<int, int> map;
//        map.insert(ft::pair<int, int>(3, 42));
//        ft::map<int, int>::iterator it = map.begin();
//        it = ft::pair<int, int>(4, 42);
//        PRINT(*it);
//    }
//    exit(0);
//    {
//        ft::map<int, const int> map;
//        map.insert(ft::pair<int, const int>(3, 42));
//        ft::map<int, const int>::iterator it = map.begin();
//        it->second = 21;
//        PRINT(*it);
//    }
//    exit(0);
//    {
//        ft::set<const int> set;
//        set.insert(42);
//        SET(set);
//        *set.begin() = 21;
//        SET(set);
//    }
//    exit(0);
//    {
//        const ft::map<int, int> set;
//        ft::map<int, int>::iterator it = set.begin();
//        (void)it;
//    }
//    exit(0);
//    {
//        ft::reverse_iterator<ft::vector<const int>::const_iterator > rcit;
//        ft::reverse_iterator<ft::vector<int>::iterator > rit;
//        rcit = rit;
//        ft::vector<int> vec;
//        ft::vector<int>::const_iterator cit = vec.begin();
//        (void)cit;
//    }
//    exit(0);
//    {
//        ft::map<T1, T2> mp, mp2;
//
//        ft_insert(mp, T3(42, "lol"));
//        ft_insert(mp, T3(42, "mdr"));
//
//        ft_insert(mp, T3(50, "mdr"));
//        ft_insert(mp, T3(35, "funny"));
//
//        ft_insert(mp, T3(45, "bunny"));
//        ft_insert(mp, T3(21, "fizz"));
//        ft_insert(mp, T3(38, "buzz"));
//
//        ft_insert(mp, mp.begin(), T3(55, "fuzzy"));
//
//        ft_insert(mp2, mp2.begin(), T3(1337, "beauty"));
//        ft_insert(mp2, mp2.end(), T3(1000, "Hello"));
//        ft_insert(mp2, mp2.end(), T3(1500, "World"));
//    }
//    exit(0);
	SUBJECT("VECTOR");
    HEADER("vector() // default");
	{
    	ft::vector<int> vector;
	}
	HEADER("vector(allocator_type) // default");
	{
		std::allocator<int> alloc;
		ft::vector<int> vector(alloc);
	}
	HEADER("vector(size_type) // fill");
	{
		ft::vector<int> vector(3);
	}
	HEADER("vector(size_type, value_type) // fill");
	{
		ft::vector<int> vector(3, 2);
	}
	HEADER("vector(size_type, value_type, allocator_type) // fill");
	{
		std::allocator<int> alloc;
		ft::vector<int> vector(3, 2, alloc);
	}
	HEADER("vector(input_iterator, input_iterator) // range");
	{
		ft::vector<int> vector(3, 2);
		ft::vector<int> vector2(vector.begin(), vector.end());
	}
	HEADER("vector(input_iterator, input_iterator, allocator_type) // range");
	{
		ft::vector<int> vector(3, 2);
		std::allocator<int> alloc;
		ft::vector<int> vector2(vector.begin(), vector.end(), alloc);
	}
	HEADER("vector(vector) // copy");
	{
		ft::vector<int> vector(3);
		ft::vector<int> vector2(vector);
	}
	HEADER("~vector()");
	{
		ft::vector<int> vector;
	}
	HEADER("operator=()");
	{
		ft::vector<int> vector(3);
		ft::vector<int> vector2;
		vector2 = vector;
	}
	HEADER("operator=() deep test");
	{
		ft::vector<test> vector;
		vector.reserve(5);
		for (int i = 0; i < 3; ++i)
			vector.push_back(test(30 + i));
		ft::vector<test> vector2;
		for (int i = 0; i < 2; ++i)
			vector2.push_back(test(10 + i));
		PRINT("");
		vector2 = vector;
		VECTOR(vector2);
	}
	HEADER("assign(size_type, value_type) // fill");
	{
		ft::vector<int> vector;
		vector.reserve(10);
		vector.push_back(40);
		vector.push_back(41);
		vector.push_back(42);
		PRINT(vector.capacity());
		vector.assign(2, 30);
		PRINT(vector.capacity());
	}
	HEADER("assign(input_iterator, input_iterator) // range");
	{
		ft::vector<int> vector;
		vector.reserve(10);
		vector.push_back(40);
		vector.push_back(41);
		vector.push_back(42);
		ft::vector<int> vector2;
		vector2.reserve(8);
		PRINT(vector2.capacity());
		vector2.assign(vector.begin(), vector.end());
		PRINT(vector2.capacity());
	}
	HEADER("at()");
	{
		ft::vector<int> vector;
		try {
			vector.at(0);
		} catch (std::out_of_range &e) {
			PRINT(e.what());
		}
		vector.push_back(42);
		PRINT(vector.at(0));
	}
	HEADER("at() const");
	{
		const ft::vector<int> vector(3, 42);
		try {
			vector.at(3);
		} catch (std::out_of_range &e) {
			PRINT(e.what());
		}
		PRINT(vector.at(0));
	}
	HEADER("operator[]()");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		PRINT(vector[0]);
	}
	HEADER("operator[]() const");
	{
		const ft::vector<int> vector(3, 42);
		PRINT(vector.at(0));
	}
	HEADER("front()");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		PRINT(vector.front());
	}
	HEADER("front() const");
	{
		const ft::vector<int> vector(3, 42);
		PRINT(vector.front());
	}
	HEADER("back()");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		PRINT(vector.back());
	}
	HEADER("back() const");
	{
		ft::vector<int> vector0;
		vector0.push_back(1);
		vector0.push_back(2);
		const ft::vector<int> vector(vector0.begin(), vector0.end());
		PRINT(vector.back());
	}
	HEADER("data()");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		PRINT(*vector.data());
	}
	HEADER("data() const");
	{
		const ft::vector<int> vector(3, 42);
		PRINT(*vector.data());
	}
	HEADER("begin()");
	{
		ft::vector<int> vector;
		vector.begin();
	}
	HEADER("begin() const");
	{
		const ft::vector<int> vector;
		vector.begin();
	}
	HEADER("end()");
	{
		ft::vector<int> vector;
		vector.end();
	}
	HEADER("end() const");
	{
		const ft::vector<int> vector;
		vector.end();
	}
	HEADER("rbegin()");
	{
		ft::vector<int> vector;
		vector.rbegin();
	}
	HEADER("rbegin() const");
	{
		const ft::vector<int> vector;
		vector.rbegin();
	}
	HEADER("rend()");
	{
		ft::vector<int> vector;
		vector.rend();
	}
	HEADER("rend() const");
	{
		const ft::vector<int> vector;
		vector.rend();
	}
	HEADER("empty() const");
	{
		ft::vector<int> vector;
		PRINT(vector.empty());
	}
	HEADER("size() const");
	{
		ft::vector<int> vector;
		PRINT(vector.size());
	}
	HEADER("max_size() const");
	{
		ft::vector<int> vector;
		PRINT(vector.max_size());
	}
	HEADER("reserve()");
	{
		ft::vector<int> vector;
		PRINT(vector.capacity());
		vector.reserve(10);
		PRINT(vector.capacity());
		try {
			vector.reserve(vector.max_size() + 1);
			PRINT("reserve(max_size() + 1) FAIL");
		} catch (std::length_error &e) {
			PRINT(e.what() << ": OK");
		}
	}
	HEADER("capacity() const");
	{
		ft::vector<int> vector;
		PRINT(vector.capacity());
	}
	HEADER("clear()");
	{
		ft::vector<int> vector;
		PRINT(vector.capacity() << " " << vector.size());
		vector.push_back(42);
		PRINT(vector.capacity() << " " << vector.size());
		vector.clear();
		PRINT(vector.capacity() << " " << vector.size());
	}
	HEADER("insert(iterator, value_type) // single element");
	{
		ft::vector<int> vector;
		vector.insert(vector.begin(), 42);
	}
	HEADER("insert(iterator, value_type) deep test // single element");
	{
		try {
			ft::vector<test> vector;
			PRINT(vector.capacity());
			vector.insert(vector.end(), test());
			PRINT(vector.capacity());
			vector.insert(vector.end(), test());
			PRINT(vector.capacity());
			vector.insert(++vector.begin(), test());
			PRINT(vector.capacity());
			vector.insert(vector.begin(), test());
			PRINT(vector.capacity());
			PRINT("");
			vector.reserve(8);
			PRINT("");
			VECTOR(vector);
			vector.insert(vector.begin(), *++vector.begin());
			VECTOR(vector);
		} catch (e_test &e) {
			PRINT("catch " << e.what());
		}
	}
	HEADER("insert(iterator, size_type, value_type) // fill");
	{
		ft::vector<int> vector;
		vector.insert(vector.begin(), 3, 42);
	}
	HEADER("insert(iterator, size_type, value_type) deep test // fill");
	{
		try {
			ft::vector<test> vector;
			PRINT(vector.capacity());
			vector.insert(vector.end(), 2, test());
			PRINT(vector.capacity());
			vector.insert(vector.end(), 2, test());
			PRINT(vector.capacity());
			vector.insert(++vector.begin(), 2, test());
			PRINT(vector.capacity());
			vector.insert(vector.begin(), 1, test());
			PRINT(vector.capacity());
			PRINT("");
			vector.reserve(16);
			PRINT("");
			VECTOR(vector);
			vector.insert(vector.begin(), 1, *++vector.begin());
			VECTOR(vector);
		} catch (e_test &e) {
			PRINT("catch " << e.what());
		}
	}
	HEADER("insert(iterator, iterator, iterator) deep test // range (input iterator)");
	{
		ft::vector<test> vector;
		vector.reserve(5);
		vector.push_back(test(3));
		vector.push_back(test(6));
		vector.push_back(test(9));

		PRINT("");
		ft::vector<test> vector2;
		vector2.reserve(3);
		vector2.push_back(test(81));
		PRINT("");
		input_iterator<test *> b = vector.begin().base();
		input_iterator<test *> e = vector.end().base();
		try {
			vector2.insert(vector2.begin(), b, e);
		} catch (e_test &e) {
			PRINT("catch " << e.what());
		}
		VECTOR(vector2);
		PRINT("");
	}
	HEADER("insert(iterator, iterator, iterator) deep test // range (random access iterator)");
	{
		ft::vector<test> vector;
		vector.reserve(5);
		vector.push_back(test(3));
		vector.push_back(test(6));
		vector.push_back(test(9));
		PRINT("");
		ft::vector<test> vector2;
		vector2.push_back(test(81));
		vector2.push_back(test(82));
		vector2.push_back(test(83));
		vector2.push_back(test(84));
		vector2.push_back(test(85));
		PRINT("");
		VECTOR(vector);
		vector.insert(vector.begin(), ++vector.begin(), --vector.end());
		VECTOR(vector);
		PRINT("");
	}
	HEADER("erase(iterator) // single element");
	{
		ft::vector<int> vector;
		vector.push_back(40);
		vector.push_back(41);
		vector.push_back(42);
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
		vector.erase(++vector.begin());
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
		vector.erase(--vector.end());
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
	}
	HEADER("erase(iterator, iterator) // range");
	{
		ft::vector<int> vector;
		vector.push_back(40);
		vector.push_back(41);
		vector.push_back(42);
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
		vector.erase(++vector.begin(), --vector.end());
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
		vector.erase(++vector.begin(), vector.end());
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
	}
	HEADER("push_back()");
	{
		ft::vector<int> vector;
		vector.push_back(42);
	}
	HEADER("push_back() deep test");
	{
		ft::vector<test> vector;
		PRINT(vector.capacity());
		vector.push_back(test());
		PRINT(vector.capacity());
		vector.push_back(test());
		PRINT(vector.capacity());
		vector.push_back(test());
		PRINT(vector.capacity());
	}
	HEADER("pop_back()");
	{
		ft::vector<int> vector;
		vector.push_back(40);
		vector.push_back(41);
		vector.push_back(42);
		PRINT(vector.size());
		VECTOR(vector);
		vector.pop_back();
		PRINT(vector.size());
		VECTOR(vector);
	}
	HEADER("resize()");
	{
		ft::vector<int> vector;
		vector.push_back(40);
		vector.push_back(41);
		vector.push_back(42);
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
		vector.resize(2);
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
		vector.resize(20);
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
		vector.resize(1);
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
		vector.resize(5);
		PRINT(vector.capacity() << " " << vector.size());
		VECTOR(vector);
		try {
			vector.resize(vector.max_size() + 1);
			PRINT("resize(max_size() + 1) FAIL");
		} catch (std::length_error &e) {
			PRINT(e.what() << ": OK");
		}
	}
	HEADER("swap()");
	{
		ft::vector<int> vector(3, 42);
		ft::vector<int> vector2;
		PRINT(vector.capacity());
		VECTOR(vector);
		PRINT(vector2.capacity());
		VECTOR(vector2);
		vector.swap(vector2);
		PRINT(vector.capacity());
		VECTOR(vector);
		PRINT(vector2.capacity());
		VECTOR(vector2);
	}
	HEADER("non-member relational operators");
	{
		ft::vector<int> vector(3, 42);
		ft::vector<int> vector2(3, 2);
		PRINT((vector == vector2));
		PRINT((vector != vector2));
		PRINT((vector < vector2));
		PRINT((vector <= vector2));
		PRINT((vector > vector2));
		PRINT((vector >= vector2));
		PRINT((vector >= vector2));
		PRINT("");
		PRINT((vector == vector));
		PRINT((vector != vector));
		PRINT((vector < vector));
		PRINT((vector <= vector));
		PRINT((vector > vector));
		PRINT((vector >= vector));
		PRINT((vector >= vector));
		PRINT("");
		PRINT((vector2 == vector));
		PRINT((vector2 != vector));
		PRINT((vector2 < vector));
		PRINT((vector2 <= vector));
		PRINT((vector2 > vector));
		PRINT((vector2 >= vector));
		PRINT((vector2 >= vector));
	}
	HEADER("non-member swap()");
	{
		ft::vector<int> vector(3, 42);
		ft::vector<int> vector2;
		PRINT(vector.capacity());
		VECTOR(vector);
		PRINT(vector2.capacity());
		VECTOR(vector2);
		swap(vector, vector2);
		PRINT(vector.capacity());
		VECTOR(vector);
		PRINT(vector2.capacity());
		VECTOR(vector2);
	}
	SUBJECT("ITERATOR");
	HEADER("iterator()");
	{
		ft::vector<int>::iterator iterator;
	}
	HEADER("iterator(iterator)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::iterator iterator = vector.begin();
		ft::vector<int>::iterator iterator2(iterator);
		IT(iterator2);
	}
	HEADER("operator=(iterator)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::iterator iterator;
		iterator = vector.begin();
		IT(iterator);
	}
    HEADER("operator iterator<const>() const");
    {
        ft::vector<int> vec(3, 42);
        (ft::vector<int>::const_iterator)vec.begin();
    }
	HEADER("base() const");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::iterator iterator = vector.begin();
		PRINT((iterator.base() == iterator.base()));
	}
	HEADER("operator*() const");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::iterator iterator = vector.begin();
		IT(iterator);
	}
	HEADER("operator->() const");
	{
		ft::vector<ft::vector<int> > vector;
		ft::vector<int> vector2;
		vector2.push_back(42);
		vector.push_back(vector2);
		ft::vector<ft::vector<int> >::iterator iterator = vector.begin();
		IT(iterator->begin());
	}
	HEADER("operator++()");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::iterator iterator = vector.begin();
		IT(iterator);
		IT((++iterator));
	}
	HEADER("operator++(int)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::iterator iterator = vector.begin();
		IT((iterator++));
		IT(iterator);
	}
	HEADER("operator--()");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::iterator iterator = --vector.end();
		IT(iterator);
		IT((--iterator));
	}
	HEADER("operator--(int)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::iterator iterator = --vector.end();
		IT((iterator--));
		IT(iterator);
	}
	HEADER("operator+=(difference_type)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::iterator iterator = vector.begin();
		IT(iterator);
		iterator += 1;
		IT(iterator);
	}
	HEADER("operator-=(difference_type)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::iterator iterator = vector.begin();
		IT(iterator);
		iterator -= 1;
		IT(iterator);
	}
	HEADER("operator[](size_t) const");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::iterator iterator = vector.begin();
		PRINT(iterator[0]);
	}
	HEADER("relational operators");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::iterator iterator = vector.begin();
		ft::vector<int>::iterator iterator2 = vector.end();
		PRINT((iterator == iterator2));
		PRINT((iterator != iterator2));
		PRINT((iterator > iterator2));
		PRINT((iterator >= iterator2));
		PRINT((iterator < iterator2));
		PRINT((iterator <= iterator2));
		PRINT("");
		PRINT((iterator == iterator));
		PRINT((iterator != iterator));
		PRINT((iterator > iterator));
		PRINT((iterator >= iterator));
		PRINT((iterator < iterator));
		PRINT((iterator <= iterator));
		PRINT("");
		PRINT((iterator2 == iterator));
		PRINT((iterator2 != iterator));
		PRINT((iterator2 > iterator));
		PRINT((iterator2 >= iterator));
		PRINT((iterator2 < iterator));
		PRINT((iterator2 <= iterator));
	}
	HEADER("operator+(difference_type)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::iterator iterator = vector.begin();
		PRINT(*(iterator + 1));
	}
	HEADER("operator-(difference_type)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::iterator iterator = vector.end();
		PRINT(*(iterator - 1));
	}
	HEADER("operator-(iterator)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::iterator iterator = vector.begin();
		ft::vector<int>::iterator iterator2 = vector.end();
		PRINT((iterator2 - iterator));
	}
	HEADER("non-member operator+(difference_type, iterator)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::iterator iterator = vector.begin();
		PRINT(*(1 + iterator));
	}
	SUBJECT("REVERSE ITERATOR");
	HEADER("reverse_iterator()");
	{
		ft::vector<int>::reverse_iterator reverse_iterator;
	}
	HEADER("reverse_iterator(Iter)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::iterator iterator = vector.end();
		ft::vector<int>::reverse_iterator reverse_iterator(iterator);
		PRINT(*reverse_iterator);
	}
	HEADER("reverse_iterator(reverse_iterator)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		ft::vector<int>::reverse_iterator reverse_iterator2(reverse_iterator);
		PRINT(*reverse_iterator2);
	}
	HEADER("operator=(reverse_iterator)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::reverse_iterator reverse_iterator;
		reverse_iterator = vector.rbegin();
		PRINT(*reverse_iterator);
	}
    HEADER("operator reverse_iterator<const>() const");
    {
        ft::vector<int> vec(3, 42);
        (ft::vector<int>::const_reverse_iterator)vec.rend();
    }
	HEADER("base() const");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		PRINT((reverse_iterator.base() == reverse_iterator.base()));
	}
	HEADER("operator*() const");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		PRINT(*reverse_iterator);
	}
	HEADER("operator->() const");
	{
		ft::vector<ft::vector<int> > vector;
		ft::vector<int> vector2;
		vector2.push_back(42);
		vector.push_back(vector2);
		ft::vector<ft::vector<int> >::reverse_iterator reverse_iterator = vector.rbegin();
		PRINT(*reverse_iterator->rbegin());
	}
	HEADER("operator++()");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		PRINT(*reverse_iterator);
		PRINT(*(++reverse_iterator));
	}
	HEADER("operator++(int)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		PRINT(*(reverse_iterator++));
		PRINT(*reverse_iterator);
	}
	HEADER("operator--()");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::reverse_iterator reverse_iterator = --vector.rend();
		PRINT(*reverse_iterator);
		PRINT(*(--reverse_iterator));
	}
	HEADER("operator--(int)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::reverse_iterator reverse_iterator = --vector.rend();
		PRINT(*(reverse_iterator--));
		PRINT(*reverse_iterator);
	}
	HEADER("operator+=(difference_type)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		PRINT(*reverse_iterator);
		reverse_iterator += 1;
		PRINT(*reverse_iterator);
	}
	HEADER("operator-=(difference_type)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rend();
		reverse_iterator -= 1;
		PRINT(*reverse_iterator);
		reverse_iterator -= 1;
		PRINT(*reverse_iterator);
	}
	HEADER("operator[](size_t) const");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		PRINT(reverse_iterator[0]);
	}
	HEADER("relational operators");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		ft::vector<int>::reverse_iterator reverse_iterator2 = vector.rend();
		PRINT((reverse_iterator == reverse_iterator2));
		PRINT((reverse_iterator != reverse_iterator2));
		PRINT((reverse_iterator > reverse_iterator2));
		PRINT((reverse_iterator >= reverse_iterator2));
		PRINT((reverse_iterator < reverse_iterator2));
		PRINT((reverse_iterator <= reverse_iterator2));
		PRINT("");
		PRINT((reverse_iterator == reverse_iterator));
		PRINT((reverse_iterator != reverse_iterator));
		PRINT((reverse_iterator > reverse_iterator));
		PRINT((reverse_iterator >= reverse_iterator));
		PRINT((reverse_iterator < reverse_iterator));
		PRINT((reverse_iterator <= reverse_iterator));
		PRINT("");
		PRINT((reverse_iterator2 == reverse_iterator));
		PRINT((reverse_iterator2 != reverse_iterator));
		PRINT((reverse_iterator2 > reverse_iterator));
		PRINT((reverse_iterator2 >= reverse_iterator));
		PRINT((reverse_iterator2 < reverse_iterator));
		PRINT((reverse_iterator2 <= reverse_iterator));
	}
	HEADER("operator+(difference_type)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		PRINT(*(reverse_iterator + 1));
	}
	HEADER("operator-(difference_type)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rend();
		PRINT(*(reverse_iterator - 1));
	}
	HEADER("operator-(reverse_iterator)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		ft::vector<int>::reverse_iterator reverse_iterator2 = vector.rend();
		PRINT((reverse_iterator2 - reverse_iterator));
	}
	HEADER("non-member operator+(difference_type, reverse_iterator)");
	{
		ft::vector<int> vector;
		vector.push_back(42);
		vector.push_back(43);
		ft::vector<int>::reverse_iterator reverse_iterator = vector.rbegin();
		PRINT(*(1 + reverse_iterator));
	}
	SUBJECT("MAP");
	HEADER("map() // default");
	{
		ft::map<int, int> map;
	}
	HEADER("map(key_compare) // default");
	{
		ft::map<int, int> map(std::less<int>);
	}
	HEADER("map(key_compare, allocator_type) // default");
	{
		ft::map<int, int> map(std::less<int>, std::allocator<ft::pair<const int, int> >);
	}
	HEADER("map(input_iterator, input_iterator) // range");
	{
		ft::map<int, int> map;
		map.insert(ft::pair<int, int>(1, 2));
		ft::map<int, int> map2(map.begin(), map.end());
		MAP(map2);
	}
	HEADER("map(const map &) // copy");
	{
		ft::map<int, int> map;
		map.insert(ft::pair<int, int>(1, 2));
		ft::map<int, int> map2(map);
		MAP(map2);
	}
	HEADER("~map()");
	{
		ft::map<int, int> map;
	}
	HEADER("operator=()");
	{
		ft::map<int, int> map;
		map.insert(ft::pair<int, int>(1, 2));
		ft::map<int, int> map2;
		map2 = map;
		MAP(map2);
	}
	HEADER("begin()");
	{
		ft::map<int, int> map;
		map.insert(ft::pair<int, int>(1, 2));
		IT_MAP(map.begin());
	}
	HEADER("begin() const");
	{
		ft::map<int, int> map0;
		map0.insert(ft::pair<int, int>(1, 2));
		const ft::map<int, int> &map = map0;
		IT_MAP(map.begin());
	}
	HEADER("end()");
	{
		ft::map<int, int> map;
		map.insert(ft::pair<int, int>(1, 2));
		IT_MAP((--map.end()));
	}
	HEADER("end() const");
	{
		ft::map<int, int> map0;
		map0.insert(ft::pair<int, int>(1, 2));
		const ft::map<int, int> &map = map0;
		IT_MAP((--map.end()));
	}
	HEADER("rbegin()");
	{
		ft::map<int, int> map;
		map.insert(ft::pair<int, int>(1, 2));
		IT_MAP(map.rbegin());
	}
	HEADER("rbegin() const");
	{
		ft::map<int, int> map0;
		map0.insert(ft::pair<int, int>(1, 2));
		const ft::map<int, int> &map = map0;
		IT_MAP(map.rbegin());
	}
	HEADER("rend()");
	{
		ft::map<int, int> map;
		map.insert(ft::pair<int, int>(1, 2));
		IT_MAP((--map.rend()));
	}
	HEADER("rend() const");
	{
		ft::map<int, int> map0;
		map0.insert(ft::pair<int, int>(1, 2));
		const ft::map<int, int> &map = map0;
		IT_MAP((--map.rend()));
	}
    HEADER("operator iterator<const>() const");
    {
        ft::map<int, int> map;
        map.insert(ft::pair<int, int>(1, 2));
        (ft::map<int, int>::const_iterator)map.begin();
    }
    HEADER("operator reverse_iterator<const>() const");
    {
        ft::map<int, int> map;
        map.insert(ft::pair<int, int>(1, 2));
        (ft::map<int, int>::const_reverse_iterator)map.rend();
    }
	HEADER("empty() const");
	{
		ft::map<int, int> map;
		PRINT(map.empty());
		map.insert(ft::pair<int, int>(1, 2));
		PRINT(map.empty());
	}
	HEADER("size() const");
	{
		ft::map<int, int> map;
		PRINT(map.size());
		map.insert(ft::pair<int, int>(1, 2));
		PRINT(map.size());
	}
	HEADER("max_size() const");
	{
		ft::map<int, int> map;
		PRINT(map.max_size());
	}
	HEADER("operator[](key_type)");
	{
		ft::map<int, int> map;
		PRINT(map.size());
		PRINT(map[1]);
		PRINT(map.size());
		map[1] = 2;
		PRINT(map.size());
		PRINT(map[1]);
		PRINT(map.size());
	}
    HEADER("at(key_type)");
    {
        ft::map<int, int> map;
        PRINT(map.size());
        try
        {
            PRINT(map.at(1));
        }
        catch (const std::out_of_range &e)
        {
            PRINT(e.what());
        }
        map.insert(ft::pair<int, int>(1, 2));
        PRINT(map.size());
        PRINT(map.at(1));
        map.at(1) = 3;
        PRINT(map.at(1));
    }
    HEADER("at(key_type) const");
    {
        ft::map<int, int> map0;
        const ft::map<int, int> &map = map0;
        PRINT(map.size());
        try
        {
            PRINT(map.at(1));
        }
        catch (const std::out_of_range &e)
        {
            PRINT(e.what());
        }
        map0.insert(ft::pair<int, int>(1, 2));
        PRINT(map.size());
        PRINT(map.at(1));
        map0.at(1) = 3;
        PRINT(map.at(1));
    }
	HEADER("insert(value_type) // single element");
	{
		ft::map<int, int> map;
		ft::pair<ft::map<int, int>::iterator, bool> inserted_pair
			= map.insert(ft::pair<int, int>(1, 2));
		IT_MAP(inserted_pair.first);
		PRINT(inserted_pair.second);
		ft::pair<ft::map<int, int>::iterator, bool> inserted_pair2
				= map.insert(ft::pair<int, int>(1, 3));
		IT_MAP(inserted_pair2.first);
		PRINT(inserted_pair2.second);
	}
	HEADER("insert(iterator, value_type &) // with hint");
	{
		ft::map<int, int> map;
		ft::pair<ft::map<int, int>::iterator, bool> inserted_pair
            = map.insert(ft::pair<int, int>(1, 1));
		IT_MAP(inserted_pair.first);
		PRINT(inserted_pair.second);
		ft::map<int, int>::iterator inserted_pair2
            = map.insert(map.end(), ft::pair<int, int>(3, 3));
		IT_MAP(inserted_pair2);
		MAP(map);
        ft::map<int, int>::iterator inserted_pair3
            = map.insert(inserted_pair.first, ft::pair<int, int>(2, 2));
        IT_MAP(inserted_pair3);
        MAP(map);
	}
    HEADER("insert(input_iterator, input_iterator) // range");
    {
        ft::map<int, int> map0;
        for (int i = 1; i < 6; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        ft::map<int, int> map;
        map.insert(++map0.begin(), --map0.end());
        MAP(map);
    }
    HEADER("erase(iterator)");
    {
        ft::map<int, int> map0;
        for (int i = 1; i < 6; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        map0.erase(map0.begin());
        map0.erase(--map0.end());
        MAP(map0);
    }
    HEADER("size_type erase(const key_type &)");
    {
        ft::map<int, int> map0;
        for (int i = 1; i < 6; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        map0.erase(1);
        map0.erase(5);
        MAP(map0);
    }
    HEADER("void erase(iterator, iterator)");
    {
        ft::map<int, int> map0;
        for (int i = 1; i < 6; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        map0.erase(++map0.begin(), --map0.end());
        MAP(map0);
    }
    HEADER("void swap(map &)");
    {
        ft::map<int, int> map0;
        for (int i = 1; i < 6; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        ft::map<int, int> map;
        map.swap(map0);
        for (int i = 10; i < 16; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        MAP(map0);
        MAP(map);
    }
    HEADER("void clear()");
    {
        ft::map<int, int> map0;
        for (int i = 1; i < 6; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        MAP(map0);
        map0.clear();
        MAP(map0);
    }
    HEADER("key_compare key_comp() const");
    {
        ft::map<int, int> map;
        PRINT(map.key_comp()(1, 2));
        PRINT(map.key_comp()(2, 2));
    }
    HEADER("value_compare value_comp() const");
    {
        ft::map<int, int> map;
        PRINT(map.value_comp()(ft::pair<int, int>(1, 1), ft::pair<int, int>(2, 2)));
        PRINT(map.value_comp()(ft::pair<int, int>(2, 2), ft::pair<int, int>(2, 2)));
    }
    HEADER("iterator find(const key_type &)");
    {
        ft::map<int, int> map;
        for (int i = 1; i < 6; ++i)
            map.insert(ft::pair<int, int>(i, i));
        IT_MAP(map.find(4));
        PRINT((map.find(6) == map.end()));
    }
    HEADER("const_iterator find(const key_type &) const");
    {
        ft::map<int, int> map0;
        for (int i = 1; i < 6; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        const ft::map<int, int> &map = map0;
        IT_MAP(map.find(4));
        PRINT((map.find(6) == map.end()));
    }
    HEADER("size_type count(const key_type &) const");
    {
        ft::map<int, int> map;
        for (int i = 1; i < 6; ++i)
            map.insert(ft::pair<int, int>(i, i));
        PRINT(map.count(4));
        PRINT(map.count(6));
    }
    HEADER("iterator lower_bound(const key_type &)");
    {
        ft::map<int, int> map;
        for (int i = 1; i < 6; ++i)
            map.insert(ft::pair<int, int>(i, i));
        IT_MAP(map.lower_bound(-1));
        IT_MAP(map.lower_bound(4));
        PRINT((map.lower_bound(6) == map.end()));
    }
    HEADER("const_iterator lower_bound(const key_type &) const");
    {
        ft::map<int, int> map0;
        for (int i = 1; i < 6; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        const ft::map<int, int> &map = map0;
        IT_MAP(map.lower_bound(-1));
        IT_MAP(map.lower_bound(4));
        PRINT((map.lower_bound(6) == map.end()));
    }
    HEADER("iterator upper_bound(const key_type &)");
    {
        ft::map<int, int> map;
        for (int i = 1; i < 6; ++i)
            map.insert(ft::pair<int, int>(i, i));
        IT_MAP(map.upper_bound(-1));
        IT_MAP(map.upper_bound(4));
        PRINT((map.upper_bound(6) == map.end()));
    }
    HEADER("const_iterator upper_bound(const key_type &) const");
    {
        ft::map<int, int> map0;
        for (int i = 1; i < 6; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        const ft::map<int, int> &map = map0;
        IT_MAP(map.upper_bound(-1));
        IT_MAP(map.upper_bound(4));
        PRINT((map.upper_bound(6) == map.end()));
    }
    HEADER("pair<iterator, iterator> equal_range(const key_type &)");
    {
        ft::map<int, int> map;
        for (int i = 1; i < 6; ++i)
            map.insert(ft::pair<int, int>(i, i));
        {
            ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> pair = map.equal_range(-1);
            IT_MAP(pair.first);
            IT_MAP(pair.second);
        }
        {
            ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> pair = map.equal_range(4);
            IT_MAP(pair.first);
            IT_MAP(pair.second);
        }
        {
            ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> pair = map.equal_range(6);
            PRINT((pair.first == map.end()));
            PRINT((pair.second == map.end()));
        }
    }
    HEADER("pair<const_iterator,const_iterator> equal_range(const key_type &) const");
    {
        ft::map<int, int> map0;
        for (int i = 1; i < 6; ++i)
            map0.insert(ft::pair<int, int>(i, i));
        const ft::map<int, int> &map = map0;
        {
            ft::pair<ft::map<int, int>::const_iterator, ft::map<int, int>::const_iterator> pair = map.equal_range(-1);
            IT_MAP(pair.first);
            IT_MAP(pair.second);
        }
        {
            ft::pair<ft::map<int, int>::const_iterator, ft::map<int, int>::const_iterator> pair = map.equal_range(4);
            IT_MAP(pair.first);
            IT_MAP(pair.second);
        }
        {
            ft::pair<ft::map<int, int>::const_iterator, ft::map<int, int>::const_iterator> pair = map.equal_range(6);
            PRINT((pair.first == map.end()));
            PRINT((pair.second == map.end()));
        }
    }
    HEADER("allocator_type get_allocator() const");
    {
        ft::map<int, int> map;
        ft::pair<const int, int> *p = map.get_allocator().allocate(1);
        int bytes = sizeof(ft::map<int, int>::value_type);
        PRINT("Allocated " << bytes << " bytes.");
        map.get_allocator().construct(p, ft::pair<int, int>(4, 4));
        PRINT("Constructed pair:");
        PRINT("first " << p->first);
        PRINT("second " << p->second);
        map.get_allocator().destroy(p);
        PRINT("Destroyed pair");
        map.get_allocator().deallocate(p,1);
        PRINT("Deallocated " << bytes << " bytes.");
    }
    HEADER("non-member relational operators");
    {
        ft::map<int, int> map;
        map.insert(ft::pair<int, int>(3, 42));
        ft::map<int, int> map2;
        map2.insert(ft::pair<int, int>(2, 2));
        PRINT((map == map2));
        PRINT((map != map2));
        PRINT((map < map2));
        PRINT((map <= map2));
        PRINT((map > map2));
        PRINT((map >= map2));
        PRINT((map >= map2));
        PRINT("");
        PRINT((map == map));
        PRINT((map != map));
        PRINT((map < map));
        PRINT((map <= map));
        PRINT((map > map));
        PRINT((map >= map));
        PRINT((map >= map));
        PRINT("");
        PRINT((map2 == map));
        PRINT((map2 != map));
        PRINT((map2 < map));
        PRINT((map2 <= map));
        PRINT((map2 > map));
        PRINT((map2 >= map));
        PRINT((map2 >= map));
    }
    HEADER("non-member swap()");
    {
        ft::map<int, int> map;
        map.insert(ft::pair<int, int>(3, 42));
        ft::map<int, int> map2;
        map.insert(ft::pair<int, int>(2, 2));
        MAP(map);
        MAP(map2);
        swap(map, map2);
        MAP(map);
        MAP(map2);
    }
    SUBJECT("STACK");
    HEADER("explicit stack() // default");
    {
        ft::stack<int, ft::vector<int> > stack;
    }
    HEADER("explicit stack(const container_type &) // default");
    {
        ft::vector<int> vector;
        ft::stack<int, ft::vector<int> > stack(vector);
    }
    HEADER("stack(const stack &) // copy");
    {
        ft::vector<int> vector;
        vector.push_back(4);
        vector.push_back(6);
        vector.push_back(9);
        ft::stack<int, ft::vector<int> > stack(vector);
        ft::stack<int, ft::vector<int> > stack2(stack);
        STACK(stack2);
    }
    HEADER("~stack()");
    {
        ft::stack<int, ft::vector<int> > stack;
    }
    HEADER("stack &operator=(const stack &)");
    {
        ft::vector<int> vector;
        vector.push_back(4);
        vector.push_back(6);
        vector.push_back(9);
        ft::stack<int, ft::vector<int> > stack(vector);
        ft::stack<int, ft::vector<int> > stack2;
        stack2 = stack;
        STACK(stack2);
    }
    HEADER("value_type &top()");
    {
        ft::vector<int> vector;
        vector.push_back(4);
        vector.push_back(6);
        vector.push_back(9);
        ft::stack<int, ft::vector<int> > stack(vector);
        PRINT(stack.top());
        stack.push(2);
        PRINT(stack.top());
    }
    HEADER("const value_type &top() const");
    {
        ft::vector<int> vector;
        vector.push_back(4);
        vector.push_back(6);
        vector.push_back(9);
        ft::stack<int, ft::vector<int> > stack0(vector);
        const ft::stack<int, ft::vector<int> > &stack = stack0;
        PRINT(stack.top());
        stack0.push(2);
        PRINT(stack.top());
    }
    HEADER("bool empty() const");
    {
        ft::stack<int, ft::vector<int> > stack;
        PRINT(stack.empty());
        stack.push(2);
        PRINT(stack.empty());
    }
    HEADER("size_type size() const");
    {
        ft::stack<int, ft::vector<int> > stack;
        PRINT(stack.size());
        stack.push(2);
        PRINT(stack.size());
    }
    HEADER("void push(const value_type &)");
    {
        ft::stack<int, ft::vector<int> > stack;
        PRINT(stack.size());
        stack.push(2);
        PRINT(stack.size());
    }
    HEADER("void pop()");
    {
        ft::stack<int, ft::vector<int> > stack;
        PRINT(stack.size());
        stack.push(2);
        PRINT(stack.size());
        stack.pop();
        PRINT(stack.size());
    }
    HEADER("non-member relational operators");
    {
        ft::stack<int, ft::vector<int> > stack;
        stack.push(3);
        ft::stack<int, ft::vector<int> > stack2;
        stack2.push(2);
        PRINT((stack == stack2));
        PRINT((stack != stack2));
        PRINT((stack < stack2));
        PRINT((stack <= stack2));
        PRINT((stack > stack2));
        PRINT((stack >= stack2));
        PRINT((stack >= stack2));
        PRINT("");
        PRINT((stack == stack));
        PRINT((stack != stack));
        PRINT((stack < stack));
        PRINT((stack <= stack));
        PRINT((stack > stack));
        PRINT((stack >= stack));
        PRINT((stack >= stack));
        PRINT("");
        PRINT((stack2 == stack));
        PRINT((stack2 != stack));
        PRINT((stack2 < stack));
        PRINT((stack2 <= stack));
        PRINT((stack2 > stack));
        PRINT((stack2 >= stack));
        PRINT((stack2 >= stack));
    }
    SUBJECT("SET");
    HEADER("set() // default");
    {
        ft::set<int, int> set;
    }
    HEADER("set(key_compare &) // default");
    {
        ft::set<int, int> set(std::less<int>);
    }
    HEADER("set(key_compare &, allocator_type &) // default");
    {
        ft::set<int, int> set(std::less<int>, std::allocator<int>);
    }
    HEADER("set(input_iterator, input_iterator) // range");
    {
        ft::set<int> set;
        set.insert(1);
        ft::set<int> set2(set.begin(), set.end());
        SET(set2);
    }
    HEADER("set(const set &) // copy");
    {
        ft::set<int> set;
        set.insert(1);
        ft::set<int> set2(set);
        SET(set2);
    }
    HEADER("~set()");
    {
        ft::set<int> set;
    }
    HEADER("set &operator=(const set &)");
    {
        ft::set<int> set;
        set.insert(1);
        ft::set<int> set2;
        set2 = set;
        SET(set2);
    }
    HEADER("iterator begin()");
    {
        ft::set<int> set;
        set.insert(1);
        IT_SET(set.begin());
    }
    HEADER("const_iterator begin() const");
    {
        ft::set<int> set0;
        set0.insert(1);
        const ft::set<int> &set = set0;
        IT_SET(set.begin());
    }
    HEADER("iterator end()");
    {
        ft::set<int> set;
        set.insert(1);
        IT_SET((--set.end()));
    }
    HEADER("const_iterator end() const");
    {
        ft::set<int> set0;
        set0.insert(1);
        const ft::set<int> &set = set0;
        IT_SET((--set.end()));
    }
    HEADER("reverse_iterator rbegin()");
    {
        ft::set<int> set;
        set.insert(1);
        IT_SET(set.rbegin());
    }
    HEADER("const_reverse_iterator rbegin() const");
    {
        ft::set<int> set0;
        set0.insert(1);
        const ft::set<int> &set = set0;
        IT_SET(set.rbegin());
    }
    HEADER("reverse_iterator rend()");
    {
        ft::set<int> set;
        set.insert(1);
        IT_SET((--set.rend()));
    }
    HEADER("const_reverse_iterator rend() const");
    {
        ft::set<int> set0;
        set0.insert(1);
        const ft::set<int> &set = set0;
        IT_SET((--set.rend()));
    }
    HEADER("operator iterator<const>() const");
    {
        ft::set<int> set;
        set.insert(1);
        (ft::set<int>::const_iterator)set.begin();
    }
    HEADER("operator reverse_iterator<const>() const");
    {
        ft::set<int> set;
        set.insert(1);
        (ft::set<int>::const_reverse_iterator)set.rend();
    }
    HEADER("bool empty() const");
    {
        ft::set<int> set;
        PRINT(set.empty());
        set.insert(1);
        PRINT(set.empty());
    }
    HEADER("size_type size() const");
    {
        ft::set<int> set;
        PRINT(set.size());
        set.insert(1);
        PRINT(set.size());
    }
    HEADER("size_type max_size() const");
    {
        ft::set<double, std::less<double>, std::allocator<double> > set;
        PRINT(set.max_size());
    }
    HEADER("insert(value_type &) // single element");
    {
        ft::set<int> set;
        ft::pair<ft::set<int>::iterator, bool> inserted_pair
            = set.insert(1);
        IT_SET(inserted_pair.first);
        PRINT(inserted_pair.second);
        ft::pair<ft::set<int>::iterator, bool> inserted_pair2
                = set.insert(1);
        IT_SET(inserted_pair2.first);
        PRINT(inserted_pair2.second);
    }
    HEADER("insert(iterator, value_type &) // with hint");
    {
        ft::set<int> set;
        ft::pair<ft::set<int>::iterator, bool> inserted_pair
            = set.insert(1);
        IT_SET(inserted_pair.first);
        PRINT(inserted_pair.second);
        ft::set<int>::iterator inserted_pair2
            = set.insert(set.end(), 3);
        IT_SET(inserted_pair2);
        SET(set);
        ft::set<int>::iterator inserted_pair3
            = set.insert(inserted_pair.first, 2);
        IT_SET(inserted_pair3);
        SET(set);
    }
    HEADER("insert(input_iterator, input_iterator) // range");
    {
        ft::set<int> set0;
        for (int i = 1; i < 6; ++i)
            set0.insert(i);
        ft::set<int> set;
        set.insert(++set0.begin(), --set0.end());
        SET(set);
    }
    HEADER("void erase(iterator)");
    {
        ft::set<int> set0;
        for (int i = 1; i < 6; ++i)
            set0.insert(i);
        set0.erase(set0.begin());
        set0.erase(--set0.end());
        SET(set0);
    }
    HEADER("size_type erase(const key_type &)");
    {
        ft::set<int> set0;
        for (int i = 1; i < 6; ++i)
            set0.insert(i);
        set0.erase(1);
        set0.erase(5);
        SET(set0);
    }
    HEADER("void erase(iterator, iterator)");
    {
        ft::set<int> set0;
        for (int i = 1; i < 6; ++i)
            set0.insert(i);
        set0.erase(++set0.begin(), --set0.end());
        SET(set0);
    }
    HEADER("void swap(set &)");
    {
        ft::set<int> set0;
        for (int i = 1; i < 6; ++i)
            set0.insert(i);
        ft::set<int> set;
        set.swap(set0);
        for (int i = 10; i < 16; ++i)
            set0.insert(i);
        SET(set0);
        SET(set);
    }
    HEADER("void clear()");
    {
        ft::set<int> set0;
        for (int i = 1; i < 6; ++i)
            set0.insert(i);
        SET(set0);
        set0.clear();
        SET(set0);
    }
    HEADER("key_compare key_comp() const");
    {
        ft::set<int> set;
        PRINT(set.key_comp()(1, 2));
        PRINT(set.key_comp()(2, 2));
    }
    HEADER("value_compare value_comp() const");
    {
        ft::set<int> set;
        PRINT(set.value_comp()(1, 2));
        PRINT(set.value_comp()(2, 2));
    }
    HEADER("iterator find(const key_type &)");
    {
        ft::set<int> set;
        for (int i = 1; i < 6; ++i)
            set.insert(i);
        IT_SET(set.find(4));
        PRINT((set.find(6) == set.end()));
    }
    HEADER("const_iterator find(const key_type &) const");
    {
        ft::set<int> set0;
        for (int i = 1; i < 6; ++i)
            set0.insert(i);
        const ft::set<int> &set = set0;
        IT_SET(set.find(4));
        PRINT((set.find(6) == set.end()));
    }
    HEADER("size_type count(const key_type &) const");
    {
        ft::set<int> set;
        for (int i = 1; i < 6; ++i)
            set.insert(i);
        PRINT(set.count(4));
        PRINT(set.count(6));
    }
    HEADER("iterator lower_bound(const key_type &)");
    {
        ft::set<int> set;
        for (int i = 1; i < 6; ++i)
            set.insert(i);
        IT_SET(set.lower_bound(-1));
        IT_SET(set.lower_bound(4));
        PRINT((set.lower_bound(6) == set.end()));
    }
    HEADER("const_iterator lower_bound(const key_type &) const");
    {
        ft::set<int> set0;
        for (int i = 1; i < 6; ++i)
            set0.insert(i);
        const ft::set<int> &set = set0;
        IT_SET(set.lower_bound(-1));
        IT_SET(set.lower_bound(4));
        PRINT((set.lower_bound(6) == set.end()));
    }
    HEADER("iterator upper_bound(const key_type &)");
    {
        ft::set<int> set;
        for (int i = 1; i < 6; ++i)
            set.insert(i);
        IT_SET(set.upper_bound(-1));
        IT_SET(set.upper_bound(4));
        PRINT((set.upper_bound(6) == set.end()));
    }
    HEADER("const_iterator upper_bound(const key_type &) const");
    {
        ft::set<int> set0;
        for (int i = 1; i < 6; ++i)
            set0.insert(i);
        const ft::set<int> &set = set0;
        IT_SET(set.upper_bound(-1));
        IT_SET(set.upper_bound(4));
        PRINT((set.upper_bound(6) == set.end()));
    }
    HEADER("pair<iterator, iterator> equal_range(const key_type &)");
    {
        ft::set<int> set;
        for (int i = 1; i < 6; ++i)
            set.insert(i);
        {
            ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> pair = set.equal_range(-1);
            IT_SET(pair.first);
            IT_SET(pair.second);
        }
        {
            ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> pair = set.equal_range(4);
            IT_SET(pair.first);
            IT_SET(pair.second);
        }
        {
            ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> pair = set.equal_range(6);
            PRINT((pair.first == set.end()));
            PRINT((pair.second == set.end()));
        }
    }
    HEADER("pair<const_iterator, const_iterator> equal_range(const key_type &) const");
    {
        ft::set<int> set0;
        for (int i = 1; i < 6; ++i)
            set0.insert(i);
        const ft::set<int> &set = set0;
        {
            ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> pair = set.equal_range(-1);
            IT_SET(pair.first);
            IT_SET(pair.second);
        }
        {
            ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> pair = set.equal_range(4);
            IT_SET(pair.first);
            IT_SET(pair.second);
        }
        {
            ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> pair = set.equal_range(6);
            PRINT((pair.first == set.end()));
            PRINT((pair.second == set.end()));
        }
    }
    HEADER("allocator_type get_allocator() const");
    {
        ft::set<int> set;
        int *p = set.get_allocator().allocate(1);
        int bytes = sizeof(ft::set<int>::value_type);
        PRINT("Allocated " << bytes << " bytes.");
        set.get_allocator().construct(p, 4);
        PRINT("Constructed:");
        PRINT(*p);
        set.get_allocator().destroy(p);
        PRINT("Destroyed");
        set.get_allocator().deallocate(p,1);
        PRINT("Deallocated " << bytes << " bytes.");
    }
    HEADER("non-member relational operators");
    {
        ft::set<int> set;
        set.insert(3);
        ft::set<int> set2;
        set2.insert(2);
        PRINT((set == set2));
        PRINT((set != set2));
        PRINT((set < set2));
        PRINT((set <= set2));
        PRINT((set > set2));
        PRINT((set >= set2));
        PRINT((set >= set2));
        PRINT("");
        PRINT((set == set));
        PRINT((set != set));
        PRINT((set < set));
        PRINT((set <= set));
        PRINT((set > set));
        PRINT((set >= set));
        PRINT((set >= set));
        PRINT("");
        PRINT((set2 == set));
        PRINT((set2 != set));
        PRINT((set2 < set));
        PRINT((set2 <= set));
        PRINT((set2 > set));
        PRINT((set2 >= set));
        PRINT((set2 >= set));
    }
    HEADER("non-member swap()");
    {
        ft::set<int> set;
        set.insert(3);
        ft::set<int> set2;
        set.insert(2);
        SET(set);
        SET(set2);
        swap(set, set2);
        SET(set);
        SET(set2);
    }
    return 0;
}
