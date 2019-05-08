#ifndef ___EASY__BSON_HPP__
#define ___EASY__BSON_HPP__
#include <bson/bson.h>
#include "Type.h"
#include <string>
#include <memory>
namespace nicehero
{
	class Bson
	{
	public:
		Bson(bson_t* t)
			:m_bson(t)
		{

		}
		~Bson()
		{
			if (m_bson)
			{
				bson_destroy(m_bson);
			}
		}
		operator const bson_t*() const
		{
			return m_bson;
		}
		operator bson_t*() const
		{
			return m_bson;
		}
		bool isString(const char* dotkey)
		{
			bson_iter_t iter, iter2;
			if (!m_bson
				|| !bson_iter_init(&iter, m_bson)
				|| !bson_iter_find_descendant(&iter, dotkey, &iter2))
			{
				return false;
			}
			return bson_iter_type(&iter2) == BSON_TYPE_UTF8;
		}
		std::string asString(const char* dotkey)
		{
			bson_iter_t iter, iter2;
			if (bson_iter_init(&iter, m_bson)
				&& bson_iter_find_descendant(&iter, dotkey, &iter2)
				&& BSON_ITER_HOLDS_UTF8(&iter2))
			{
				return bson_iter_utf8(&iter2, nullptr);
			}
			return "";
		}

		bool isInt64(const char* dotkey)
		{
			bson_iter_t iter, iter2;
			if (!m_bson
				|| !bson_iter_init(&iter, m_bson)
				|| !bson_iter_find_descendant(&iter, dotkey, &iter2))
			{
				return false;
			}
			return bson_iter_type(&iter2) == BSON_TYPE_INT64;
		}

		i64 asInt64(const char* dotkey)
		{
			bson_iter_t iter,iter2;
			if (bson_iter_init(&iter, m_bson)
				&& bson_iter_find_descendant(&iter, dotkey, &iter2) 
				&& BSON_ITER_HOLDS_INT64(&iter2)) 
			{
				return bson_iter_as_int64(&iter2);
			}
			return 0;
		}

		bool isNumber(const char* dotkey)
		{
			bson_iter_t iter,iter2;
			if (!m_bson 
				|| !bson_iter_init(&iter, m_bson) 
				|| !bson_iter_find_descendant(&iter, dotkey, &iter2))
			{
				return false;
			}
			
			if (iter2.value.value_type == BSON_TYPE_INT64
				|| iter2.value.value_type == BSON_TYPE_INT32
				|| iter2.value.value_type == BSON_TYPE_DECIMAL128
				|| iter2.value.value_type == BSON_TYPE_DOUBLE
				)
			{
				return true;
			}
			return false;
		}

		double asNumber(const char* dotkey)
		{
			bson_iter_t iter, iter2;
			if (bson_iter_init(&iter, m_bson)
				&& bson_iter_find_descendant(&iter, dotkey, &iter2)
				&& BSON_ITER_HOLDS_NUMBER(&iter2))
			{
				return bson_iter_as_double(&iter2);
			}
			return 0.0;
		}

		bson_t* m_bson = nullptr;
	};
	typedef std::unique_ptr<Bson> BsonPtr;
}
#ifndef NBSON
#define NBSON(...) nicehero::BsonPtr(new ::nicehero::Bson(bcon_new (NULL, __VA_ARGS__, (void *) NULL))) //BCON_NEW
#define NBSON_T(...) ::nicehero::Bson(bcon_new (NULL, __VA_ARGS__, (void *) NULL)) //BCON_NEW
#endif
#endif // !___EASY__BSON_HPP__
