#include "elasticc.h"

static void TestIndex() {
	std::string res;
	elasticc::Index(res, "localhost:9200", "twitter", "_doc", "{ \"user\":\"kimchy\",\"post_date\":\"2019-11-15T14:12:12\",\"message\":\"try elasticc\"}", 1);
	std::cout << res << std::endl;
}

static void TestTryIndex() {
	std::string res;
	elasticc::TryIndex(res, "localhost:9200", "twitter", "_doc", "{ \"user\":\"kimchy\",\"post_date\":\"2019-11-15T14:12:12\",\"message\":\"try elasticc\"}", 1);
	std::cout << res << std::endl;
}

static void TestGet() {
	std::string res;
	elasticc::Get(res, "localhost:9200", "twitter", "_doc", 1);
	std::cout << res << std::endl;
}

static void TestDelete() {
	std::string res;
	elasticc::Delete(res, "localhost:9200", "twitter", "_doc", 1);
	std::cout << res << std::endl;
}

static void TestUpdate() {
	std::string res0;
	elasticc::Index(res0, "localhost:9200", "test", "_doc", "{ \"counter\" : 1, \"tags\" : [\"red\"] }", 1);
	std::cout << res0 << std::endl;
	std::string res1;
	elasticc::Update(res1, "localhost:9200", "test", "_doc","{ \"script\" : { \"source\": \"ctx._source.counter += params.count\", \"lang\": \"painless\", \"params\" : { \"count\" : 4 } } }", 1);
	std::cout << res1 << std::endl;
}

int main()
{
	//TestIndex();
	//TestTryIndex();
	//TestGet();
	//TestDelete();
	//TestUpdate();
	std::cin.get();
	return 0;
}
