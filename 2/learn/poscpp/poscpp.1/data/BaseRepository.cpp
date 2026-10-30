#include "BaseRepository.hpp"

long Seq::last_id_ = 0;
long Seq::next() { return ++Seq::last_id_; }
