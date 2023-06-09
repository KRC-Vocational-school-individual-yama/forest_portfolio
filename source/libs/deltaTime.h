#pragma once
#include"myDxLib.h"

class DeltaTime {
public:
	DeltaTime() { time = GetNowHiPerformanceCount(); }
	//メインUpdateの一番最後に置く
	void Update() { time = GetNowHiPerformanceCount(); }
	
	float GetDeltTime() {
		return (GetNowHiPerformanceCount() - time) / 1000000;
	}
private:
	double time;
};