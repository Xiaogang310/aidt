#include "Aims.hpp"

// {{{ macros

#define INIT_KAFKA_CONSUMER(name) do { \
	_kafkaConsumerCallback##name = new aims::kafka::Consumer##name(_context);\
	_kafkaConsumer##name = new adbase::kafka::Consumer(_configure->topicNameConsumer##name,\
							_configure->groupId##name, _configure->brokerListConsumer##name);\
	_kafkaConsumer##name->setMessageHandler(std::bind(&aims::kafka::Consumer##name::pull,\
													 _kafkaConsumerCallback##name,\
													 std::placeholders::_1, std::placeholders::_2,\
													 std::placeholders::_3, std::placeholders::_4));\
	_kafkaConsumer##name->setStatCallback(std::bind(&aims::kafka::Consumer##name::stat,\
													_kafkaConsumerCallback##name,\
												    std::placeholders::_1, std::placeholders::_2));\
	_kafkaConsumer##name->setKafkaDebug(_configure->kafkaDebug##name);\
	_kafkaConsumer##name->setOffsetStorePath(_configure->offsetPath##name);\
	_kafkaConsumer##name->setKafkaStatInterval(_configure->statInterval##name);\
    if (_configure->isNewConsumer##name) {\
        _kafkaConsumer##name->setIsNewConsumer(true);\
        _kafkaConsumer##name->setOffsetStoreMethod("broker");\
    }\
} while(0)
#define START_KAFKA_CONSUMER(name) do {\
	_kafkaConsumer##name->start();\
} while(0)
#define STOP_KAFKA_CONSUMER(name) do {\
	if (_kafkaConsumer##name != nullptr) {\
		_kafkaConsumer##name->stop();\
	}\
	if (_kafkaConsumerCallback##name != nullptr) {\
		delete _kafkaConsumerCallback##name;\
		_kafkaConsumerCallback##name = nullptr;\
	}\
} while(0)

#define INIT_KAFKA_PRODUCER(name) do {\
	_kafkaProducerCallback##name = new aims::kafka::Producer##name(_context);\
	_kafkaProducer##name = new adbase::kafka::Producer(_configure->brokerListProducer##name,\
						   _configure->queueLength##name, _configure->debug##name);\
	_kafkaProducer##name->setSendHandler(std::bind(&aims::kafka::Producer##name::send,\
											   _kafkaProducerCallback##name,\
											   std::placeholders::_1, std::placeholders::_2,\
											   std::placeholders::_3));\
	_kafkaProducer##name->setErrorHandler(std::bind(&aims::kafka::Producer##name::errorCallback, \
											   _kafkaProducerCallback##name, \
											   std::placeholders::_1, std::placeholders::_2,\
											   std::placeholders::_3, std::placeholders::_4));\
} while(0)
#define START_KAFKA_PRODUCER(name) do {\
	_kafkaProducer##name->start();\
} while(0)
#define STOP_KAFKA_PRODUCER(name) do {\
	if (_kafkaProducer##name != nullptr) {\
		_kafkaProducer##name->stop();\
	}\
	if (_kafkaProducerCallback##name != nullptr) {\
		delete _kafkaProducerCallback##name;\
		_kafkaProducerCallback##name = nullptr;\
	}\
} while(0)

// }}}
// {{{ Aims::Aims()

Aims::Aims(AimsContext* context) :
	_context(context) {
	_configure = _context->config;
}

// }}}
// {{{ Aims::~Aims()

Aims::~Aims() {
}

// }}}
// {{{ void Aims::run()

void Aims::run() {
	// 初始化 server
	init();
	
	START_KAFKA_PRODUCER(In);
}

// }}}
// {{{ void Aims::init()

void Aims::init() {
	initKafkaProducer();
}

// }}}
// {{{ void Aims::stop()

void Aims::stop() {
	STOP_KAFKA_PRODUCER(In);
}

// }}}
// {{{ adbase::kafka::Producer* Aims::getProducer()

adbase::kafka::Producer* Aims::getProducer() {
    return _kafkaProducerIn;
}

// }}}
// {{{ void Aims::initKafkaProducer()

void Aims::initKafkaProducer() {
	INIT_KAFKA_PRODUCER(In);
}

// }}}
