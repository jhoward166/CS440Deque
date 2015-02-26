#include <string.h>
#include <iostream>
#include <cassert>
#define Deque_DEFINE(MyClass)\
\
\
struct Deque_##MyClass;\
struct Deque_##MyClass##_Iterator;\
\
struct Deque_##MyClass{\
	MyClass* deque;\
	int alpha;\
	int omega;\
	int qSize;\
	int maxSize;\
	char type_name[sizeof("Deque_" #MyClass )] = "Deque_"#MyClass;\
	void(*pop_front)(Deque_##MyClass*);\
	void(*pop_back)(Deque_##MyClass*);\
	void(*push_front)(Deque_##MyClass*, MyClass);\
	void(*push_back)(Deque_##MyClass*, MyClass);\
	MyClass&(*front)(Deque_##MyClass*);\
	MyClass&(*at)(Deque_##MyClass*, int);\
	MyClass&(*back)(Deque_##MyClass*);\
	Deque_##MyClass##_Iterator(*begin)(Deque_##MyClass*);\
	Deque_##MyClass##_Iterator(*end)(Deque_##MyClass*);\
	int(*size)(Deque_##MyClass*);\
	bool(*empty)(Deque_##MyClass*);\
	void(*clear)(Deque_##MyClass*);\
	void(*dtor)(Deque_##MyClass*);\
	bool(*equals)(const MyClass&, const MyClass&);\
};\
\
struct Deque_##MyClass##_Iterator{\
	Deque_##MyClass* belongTo;\
	int index;\
	void(*inc)(Deque_##MyClass##_Iterator*);\
	void(*dec)(Deque_##MyClass##_Iterator*);\
	MyClass&(*deref)(Deque_##MyClass##_Iterator*);\
};\
\
/*iterator functions*/\
void inc(Deque_##MyClass##_Iterator* ptr){\
	ptr->index += 1;\
}\
\
void dec(Deque_##MyClass##_Iterator* ptr){\
	ptr->index -= 1;\
}\
\
MyClass& deref(Deque_##MyClass##_Iterator* ptr){\
	return (ptr->belongTo->at(ptr->belongTo, ptr->index));\
}\
bool Deque_##MyClass##_Iterator_equal(Deque_##MyClass##_Iterator it1, Deque_##MyClass##_Iterator it2){\
	if((it1.belongTo == it2.belongTo) && (it1.index == it2.index)){\
		return true;\
	}else{\
		return false;\
	}\
}\
\
void Deque_##MyClass##_Iterator_ctor(Deque_##MyClass##_Iterator* ptr){\
	ptr->inc = inc;\
	ptr->dec = dec;\
	ptr->deref = deref;\
}\
/*Deque Functions*/\
/*removes item from the front of the queue*/\
void pop_front(Deque_##MyClass* ptr){\
	if(ptr->qSize !=0){\
		int index = ptr->alpha;\
		if(index == ptr->maxSize-1){\
			ptr->alpha = 0;\
		}else{\
			ptr->alpha+=1;\
		}\
		ptr->qSize-=1;\
	}\
}\
/*removes item from the back of the queue*/\
void pop_back(Deque_##MyClass* ptr){\
	if(ptr->qSize != 0){\
		int index = ptr->omega;\
		if(index == 0){\
			ptr->omega = ptr->maxSize-1;\
		}else{\
			ptr->omega-=1;\
		}\
		ptr->qSize-=1;\
	}\
}\
void moreMem(Deque_##MyClass* ptr){\
	MyClass* holdThis = (MyClass*)(malloc((ptr->qSize*2)*sizeof(MyClass)));\
	int i = 0;\
	for(Deque_##MyClass##_Iterator copier = ptr->begin(ptr); \
		!Deque_##MyClass##_Iterator_equal(copier, ptr->end(ptr)); \
		copier.inc(&copier), ++i){\
		assert(i < ptr->maxSize); \
		holdThis[i] = copier.deref(&copier);\
	}\
	free(ptr->deque);\
	ptr->maxSize = ptr->maxSize*2;\
	ptr->deque = holdThis;\
	ptr->alpha=0;\
	ptr->omega=ptr->qSize-1;\
}\
/*adds item to the front of the queue*/\
void push_front(Deque_##MyClass* ptr, MyClass obj){\
	if(ptr->qSize == ptr->maxSize){\
		moreMem(ptr);\
	}\
	if(ptr->qSize == 0){\
		ptr->alpha =0;\
		ptr->omega =0;\
		ptr->deque[0] = obj;\
	}else{\
		assert(ptr->maxSize >= ptr->alpha);\
		assert(ptr->maxSize >= ptr->omega);\
		int before = ptr->alpha;\
		if(before == 0){\
			before = ptr->maxSize;\
		}\
		ptr->deque[before-1] = obj;\
		ptr->alpha = before-1;\
	}\
	ptr->qSize++;\
}\
/*adds item to the back of the queue*/\
void push_back(Deque_##MyClass* ptr, MyClass obj){\
	if(ptr->qSize == ptr->maxSize){\
		moreMem(ptr);\
	}\
	if(ptr->qSize == 0){\
		ptr->alpha =0;\
		ptr->omega =0;\
		ptr->deque[0] = obj;\
	}else{\
		int after = ptr->omega;\
		if(after == ptr->maxSize-1){\
			after = 0;\
		}\
		ptr->deque[after+1] = obj;\
		ptr->omega = after+1;\
	}\
	ptr->qSize++;\
}\
/*first elements address*/\
Deque_##MyClass##_Iterator begin(Deque_##MyClass* ptr){\
	Deque_##MyClass##_Iterator newIt;\
 	Deque_##MyClass##_Iterator_ctor(&newIt);\
	newIt.belongTo = ptr;\
	newIt.index = 0;\
	return newIt;\
}\
/*1 after the last element*/\
Deque_##MyClass##_Iterator end(Deque_##MyClass* ptr){\
	Deque_##MyClass##_Iterator newIt;\
 	Deque_##MyClass##_Iterator_ctor(&newIt);\
	newIt.belongTo = ptr;\
	newIt.index = ptr->qSize;\
	return newIt;\
}\
/*first element*/\
MyClass& front(Deque_##MyClass* ptr){\
	return (ptr->deque[ptr->alpha]);\
}\
MyClass& at(Deque_##MyClass* ptr, int i){\
	int index = (ptr->alpha + i) % ptr->maxSize;\
	return (ptr->deque[index]);\
}\
/*last element*/\
MyClass& back(Deque_##MyClass* ptr){\
	return (ptr->deque[ptr->omega]);\
}\
int size(Deque_##MyClass* ptr){\
	return ptr->qSize;\
}\
bool empty(Deque_##MyClass* ptr){\
	if(ptr->qSize == 0){\
		return true;\
	}else{\
		return false;\
	}\
}\
void clear(Deque_##MyClass* ptr){\
	ptr->qSize = 0;\
}\
void dtor(Deque_##MyClass* ptr){\
	free(ptr->deque);\
}\
\
bool Deque_##MyClass##_equal(Deque_##MyClass first, Deque_##MyClass second){\
	if(first.qSize == second.qSize){\
		int i;\
		for(i=0; i<first.qSize; i++){\
			if(first.equals(first.at(&first,i), second.at(&second,i))||first.equals(second.at(&second, i),first.at(&first, i))){\
				return false;\
			}\
		}\
		return true;\
	}else{\
		return false;\
	}\
	\
}\
\
\
\
void Deque_##MyClass##_ctor(Deque_##MyClass* ptr, bool (*comp)(const MyClass&, const MyClass&)){\
	ptr->deque = (MyClass*) (malloc(sizeof(MyClass)));\
	ptr->maxSize = 1;\
	ptr->qSize = 0;\
	ptr->pop_front = pop_front;\
	ptr->pop_back = pop_back;\
	ptr->push_back = push_back;\
	ptr->push_front = push_front;\
	ptr->front = front;\
	ptr->at = at;\
	ptr->back = back;\
	ptr->begin = begin;\
	ptr->end = end;\
	ptr->size = size;\
	ptr->clear = clear;\
	ptr->empty = empty;\
	ptr->dtor = dtor;\
	ptr->equals = comp;\
}

