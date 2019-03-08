//CLASSE QUE CONTROLA A CRONOMETRAGEM DO TEMPO

#pragma once

#include <chrono>
#define START 0
#define END 1

class FrameTimer {

public:

	FrameTimer() {
		//define o primeiro ponto no tempo ao construir o objeto
		timeSpan[END] = std::chrono::steady_clock::now();
	}

	//cronometra e retorna o tempo decorrido entre dois pontos no tempo
	float measureTimeSpan()
	{
		using namespace std::chrono;

		//o ponto FINAL da ultima cronometragem passa a ser o novo ponto INICIAL
		timeSpan[START] = timeSpan[END];

		// cria um novo ponto FINAL (ponto "AGORA") para a nova cronometragem
		steady_clock::time_point new_tp = steady_clock::now();
		timeSpan[END] = new_tp;

		// cria uma 'duration' para armazenar o tempo decorrido entre os dois pontos de tempo
		duration<float> runtime = timeSpan[END] - timeSpan[START];

		//conta o tempo percorrido e retorna como um float
		return runtime.count();
	}

private:
	std::chrono::steady_clock::time_point timeSpan[2];
};
