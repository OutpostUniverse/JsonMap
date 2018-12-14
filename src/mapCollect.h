
template<typename Input, typename Func>
auto mapCollect(Input input, Func f) {
	using OutputType = decltype(f(*input.begin()));

	std::vector<OutputType> output;
	output.reserve(input.size());
	std::transform(input.begin(), input.end(), std::back_inserter(output), f);
	return output;
}
