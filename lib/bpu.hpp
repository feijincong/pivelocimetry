#include <cmath>
#include <algorithm>

namespace bpu {

/* Calculate the median value of a container with specified
 * return type. Original container is not modified */
template<typename To, typename Container>
To median(Container&& c);

/* Same as median but container is modified by partially 
 * sorting contents */
template<typename To, typename Container>
To median_modify_container(Container&& c);

/* Arithmetic mean of a container with specified return type */
template<typename To, typename Container>
To mean(Container&& c);

/* Static cast but rounding to nearest integer value 
 * for integral trypes */
template<typename To, typename From>
To cast_round_if_integral(const From f);

template<typename To, typename Container>
To mean(Container&& c)
{
	return cast_round_if_integral<To>(std::accumulate(c.begin(),c.end(), static_cast<To>(0)) / c.size());
}

template<typename To, typename From>
To cast_round_if_integral(const From f)
{
	if (std::is_integral<To>::value) {
		return static_cast<To>(f + 0.5);
	} else {
		return static_cast<To>(f);
	}
}

template<typename To, typename Container>
To median(Container&& c)
{
	auto cCopy = c;
	return median_modify_container<To>(cCopy);
}

template<typename To, typename Container>
To median_modify_container(Container&& c)
{
	/* Empty array returns zero */
	if (c.empty())
		return static_cast<To>(0);

	/* Single element returns the element */
	size_t cSize = c.size();
	if (cSize == 1)
		return cast_round_if_integral<To>(c[0]);

	/* Find the middle index */
	size_t mark = floor(cSize / 2);
	std::nth_element(c.begin(), c.begin() + mark, c.end());

	if (cSize % 2 != 0) {
		return cast_round_if_integral<To>(c[mark]);
	} else {
		auto median = 0.5 * (c[mark] + c[mark - 1]);
		return cast_round_if_integral<To>(median);
	}
}
}
