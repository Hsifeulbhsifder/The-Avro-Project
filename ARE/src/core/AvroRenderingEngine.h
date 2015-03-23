#ifndef AVRO_RENDERING_ENGINE_H
#define AVRO_RENDERING_ENGINE_H

struct Window;

class DLLEXPORT AvroRenderingEngine{
private:
	AvroRenderingEngine(const AvroRenderingEngine& rhs){}
	void operator=(const AvroRenderingEngine& rhs){}
	
	Window* m_window;
public:
	AvroRenderingEngine(){}

	B8 Initialize(Window* window);

	void Render(F32 delta);

	void Terminate();

	~AvroRenderingEngine(){}

};

#endif