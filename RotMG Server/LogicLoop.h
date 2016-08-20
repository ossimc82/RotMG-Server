#ifndef LOGICLOOP_H_
#define LOGICLOOP_H_

#include <thread>

class RealmManager;

class LogicLoop
{
public:
	LogicLoop(RealmManager* manager) {
		this->manager = manager;
	}
	~LogicLoop() { }
	void start();
private:
	std::thread* logicThread;
	void loop();
	void update(double time, double dt);
	RealmManager* manager;
};

#endif // !LOGICLOOP_H_
