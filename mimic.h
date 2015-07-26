// mimic.h

// Mimic Pattern: replaces slicing behavior of objects
// author: Igor Machado Coelho (igormachado at gmail dot com)
// date:   July 26, 2015
// MIT LICENSE

#ifndef MIMIC_H_
#define MIMIC_H_

#include<assert.h>
#include<iostream>

// =======================
// RULES FOR MIMIC PATTERN
// =======================
// 1-No public variables
// 2-All methods must follow the mimic pattern, otherwise undefined behavior will occur
// 3-Copy constructor cannot be used anymore (mimic will use it)
// 4-Class X must provide a virtual void clone(X*&) const method.

#define MIMIC_INIT(CLASS)     _mimic_##CLASS = NULL;
#define MIMIC_DESTROY(CLASS)  if(_mimic_##CLASS)\
                                   delete _mimic_##CLASS;
#define MIMIC_COPY(CLASS)     public:\
                              CLASS(const CLASS& a)\
                              {\
                                  _mimic_##CLASS = NULL;\
                                  if (a._mimic_##CLASS)\
                                       a._mimic_##CLASS->clone(_mimic_##CLASS);\
                                  else\
                                       a.clone(_mimic_##CLASS);\
                              };
#define MIMIC_ASSIGN(CLASS)   public:\
                              CLASS& operator=(const CLASS& m)\
                              {\
                                  if (&m == this)\
                                      return *this;\
                                  if (_mimic_##CLASS)\
                                  {\
                                      delete _mimic_##CLASS;\
                                      _mimic_##CLASS = NULL;\
                                  }\
                                  if (m._mimic_##CLASS)\
                                      m._mimic_##CLASS->clone(_mimic_##CLASS);\
                                  else\
                                      m.clone(_mimic_##CLASS);\
                                  return *this;\
                              };
#define MIMIC_VOIDFUNC(CLASS, f,...)      if(_mimic_##CLASS)\
                                          {\
                                              _mimic_##CLASS -> f ( __VA_ARGS__ );\
                                              return;\
                                          }
#define MIMIC_RETFUNC(CLASS, f,...)       if(_mimic_##CLASS)\
                                              return _mimic_##CLASS -> f ( __VA_ARGS__ );

#define MIMIC_CLONE(CLASS, BASE)           virtual void clone(BASE*& m) const\
                                           {\
                                               CLASS* a = NULL;\
                                               clone(a);\
                                               m = a;\
                                           }

#define MIMIC_BEGIN(CLASS)     private: \
                                   CLASS* _mimic_##CLASS;\
                               MIMIC_COPY(CLASS)\
                               MIMIC_ASSIGN(CLASS)\
                               private: \
 
#define DISABLE_SLICING(CLASS)             private:\
                                           template<typename T> CLASS(T const& d);\
                                           template<typename T> CLASS const& operator=(T const& rhs);

#endif /* MIMIC_H_ */
