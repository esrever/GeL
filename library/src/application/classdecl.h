#pragma once

#define DECL_GET_BREF(T,V) public: const T& Get##V##() const {return m##V ;}
#define DECL_GET_BVAL(T,V) public: const T Get##V##() const {return m##V ;}
#define DECL_SET_BREF(T,V) public: void Set##V##(const T& v) { m##V = v;}
#define DECL_SET_BVAL(T,V) public: void Set##V##(const T v) { m##V = v;}


#define DECL_RO_VAR_REF(T,V) \
	DECL_GET_BREF(T,V)\
	private: T m##V ;\
	public:

#define DECL_RO_VAR(T,V) \
	DECL_GET_BVAL(T,V)\
	private: T m##V ;\
	public:

#define DECL_RW_VAR_REF(T,V) \
	DECL_GET_BREF(T,V)\
	DECL_SET_BREF(T,V)\
	private: T m##V ;\
	public:

#define DECL_RW_VAR(T,V) \
	DECL_GET_BVAL(T,V)\
	DECL_SET_BVAL(T,V)\
	private: T m##V ;\
	public: