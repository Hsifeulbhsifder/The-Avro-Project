#ifndef AVRO_RENDERING_ENGINE_H
#define AVRO_RENDERING_ENGINE_H

class DLLEXPORT AvroRenderingEngine{
private:
	AvroRenderingEngine(const AvroRenderingEngine& rhs){}
	void operator=(const AvroRenderingEngine& rhs){}
public:
	AvroRenderingEngine(){}

	B8 Initialize();

	void Render(F32 delta);

	void Terminate();

	~AvroRenderingEngine(){}

};

#endif