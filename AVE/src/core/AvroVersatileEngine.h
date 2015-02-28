#ifndef AVRO_VERSATILE_ENGINE_H
#define AVRO_VERSATILE_ENGINE_H

class DLLEXPORT AvroVersatileEngine{
private:
	AvroVersatileEngine(const AvroVersatileEngine& rhs){}
	void operator=(const AvroVersatileEngine& rhs){}
public:
	B8 isRunning = false; // TODO: move initialization
	AvroVersatileEngine(){}

	B8 Initialize();

	void Run();

	void Terminate();

	~AvroVersatileEngine(){}

};

#endif
