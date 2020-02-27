#ifndef __HITTABLE_LIST_HPP__
#define __HITTABLE_LIST_HPP__

#include "./Hittable.hpp"

#include <memory>
#include <list>
#include <algorithm>

template<class TYPE>
class HittableList : public Hittable<TYPE>
{
	std::list<std::unique_ptr<Hittable<TYPE>>> m_list;
	public:
	HittableList(){}
	~HittableList()
	{
		m_list.clear();
	}

	// function
	bool Hit(const Ray<TYPE> &r, const TYPE &t_min, const float &t_max, HitRecord<TYPE> &rec) const override
	{
		HitRecord<TYPE> t_rec;
		bool hit_anything = false;
		TYPE closest_so_far = t_max;
		for (const auto &list_data : m_list)
		{
			if (list_data->Hit(r, t_min, closest_so_far, t_rec))
			{
				hit_anything = true;
				closest_so_far = t_rec.t;
				rec = t_rec;
			}
		}
		return hit_anything;
	}

	inline std::list<std::unique_ptr<Hittable<TYPE>>>& GetList(){ return m_list; }
};

#endif
