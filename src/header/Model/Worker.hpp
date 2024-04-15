#ifndef MODEL_WORKER_HPP
#define MODEL_WORKER_HPP

#include "Container/Storage.hpp"
#include "Model/GameObject.hpp"

// TODO: Add constraint
template <class T>
class Worker : virtual public GameObject {
protected:
	Storage<T> field;

public:
	void harvest();
	void plant();
};

#endif
