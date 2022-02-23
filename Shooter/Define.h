#pragma once

//#define PURE =0

template <typename T>
inline void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = NULL;
	}
}

#define DECLARE_SINGETON(type)\
	static type** GetInstance()\
	{\
		static type*	pInstance = new type;\
		if(pInstance == NULL)\
			pInstance = new type;\
		return &pInstance;\
	}\
	static void DestroyInstance()\
	{\
		type** ppInstance = GetInstance();\
		if(*ppInstance != NULL)\
		{\
			delete *ppInstance;\
			*ppInstance = NULL;\
		}\
	}

#define GET_SINGLE(type) (*type::GetInstance())
#define DESTROY_SINGLE(type) (*type::GetInstance())->DestroyInstance()

