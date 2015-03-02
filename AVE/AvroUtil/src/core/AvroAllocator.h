#ifndef AVRO_UTIL_ALLOCATOR_H
#define AVRO_UTIL_ALLOCATOR_H

class AvroAllocator{
public:
	AvroAllocator(){}
	virtual B8 Initialize(U64 size_bytes) = 0;
	virtual void* Allocate(U64 size_bytes) = 0;
	virtual void Dissipate(void* mem) = 0;
	virtual void Terminate() = 0;
	virtual ~AvroAllocator(){};
private:

};

//TODO: make this a singleton, so that it may be globally accessible
class AvroDefaultAllocator : public AvroAllocator{
public:
	AvroDefaultAllocator():AvroAllocator(){}
	INLINEFORCE B8 Initialize(U64 size_bytes){/*Do Nothing*/ return true; }
	INLINEFORCE void* Allocate(U64 size_bytes){ return malloc(size_bytes); }
	INLINEFORCE void Dissipate(void* mem){ free(mem); }
	INLINEFORCE void Terminate(){/*Do Nothing*/}
	~AvroDefaultAllocator(){}
private:

};

#endif