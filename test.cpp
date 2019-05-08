#include "Mongo.hpp"
#include <thread>
#include <stdio.h>
#include <memory>
#include <time.h>

void test(const char* dbconnection,const char* dbname)
{
	auto pool = std::make_shared<nicehero::MongoConnectionPool>();
	if (!pool.init(dbconnection,dbname))
	{
		printf("error db %s\n",dbconnection);
		return;
	}
	auto client = pool.popClient();
	if (!client)
	{
		return;
	}
	std::thread t([client]{
		//insert
		client->insert("easy",
			NBSON_T(
				"_id", BCON_INT64(100)
				, "hello", BCON_UTF8("world")
				, "ar"
				, "["
					, "{"
						, "hello", BCON_INT64(666)
					, "}"
					, "world5"
					, BCON_DATE_TIME(time(0) * 1000)
				, "]"
				, "oo"
				, "{"
					,"xhello", BCON_INT64(666)
				, "}"
				));
		//update
		auto obj = NBSON("$set", "{", "ar.0.hello", BCON_INT64(101), "}");
		client->update("easy",
			NBSON_T("_id", BCON_INT64(100)),
			*obj);
		//find
		auto cursor = client->find("easy", NBSON_T("_id", BCON_INT64(103)), nicehero::Bson(nullptr));
		while (auto r = cursor->fetch())
		{
			if (r->isInt64("oo.xhello"))
			{
				printf("oo.xhello: %d\n", int(r->asInt64("oo.xhello")));
			}
			if (r->isInt64("ar.0.hello"))
			{
				printf("ar.0.hello: %d\n", int(r->asInt64("ar.0.hello")));
			}
		}
	});
	t.join();
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("need param: ./test dbconnection dbname\n");
		printf("example: ./test mongodb://user:pass@localhost:27017/?authSource=admin dbname\n");
		return 0;
	}
	test(argv[1], argv[2]);
	return 0;
}