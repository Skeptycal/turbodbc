#include <turbodbc_python/determine_parameter_type.h>

#include <stdexcept>

#include <datetime.h> // Python header


namespace turbodbc {

namespace {

	struct datetime_initializer {
		datetime_initializer()
		{
			PyDateTime_IMPORT;
		}
	};

	static const datetime_initializer required_for_datetime_interaction;

	std::size_t const size_not_important = 0;

	void set_integer(pybind11::object const & value, cpp_odbc::writable_buffer_element & destination)
	{
		*reinterpret_cast<long *>(destination.data_pointer) = value.cast<long>();
		destination.indicator = sizeof(long);
	}

	void set_floating_point(pybind11::object const & value, cpp_odbc::writable_buffer_element & destination)
	{
		*reinterpret_cast<double *>(destination.data_pointer) = value.cast<double>();
		destination.indicator = sizeof(double);
	}

	void set_string(pybind11::object const & value, cpp_odbc::writable_buffer_element & destination)
	{
		auto const s = value.cast<std::string>();
		auto const length_with_null_termination = s.size() + 1;
		std::memcpy(destination.data_pointer, s.c_str(), length_with_null_termination);
		destination.indicator = s.size();
	}

	void set_date(pybind11::object const & value, cpp_odbc::writable_buffer_element & destination)
	{
		auto ptr = value.ptr();
		auto d = reinterpret_cast<SQL_DATE_STRUCT *>(destination.data_pointer);

		d->year = PyDateTime_GET_YEAR(ptr);
		d->month = PyDateTime_GET_MONTH(ptr);
		d->day = PyDateTime_GET_DAY(ptr);

		destination.indicator = sizeof(SQL_DATE_STRUCT);
	}

	void set_timestamp(pybind11::object const & value, cpp_odbc::writable_buffer_element & destination)
	{
		auto ptr = value.ptr();
		auto d = reinterpret_cast<SQL_TIMESTAMP_STRUCT *>(destination.data_pointer);

		d->year = PyDateTime_GET_YEAR(ptr);
		d->month = PyDateTime_GET_MONTH(ptr);
		d->day = PyDateTime_GET_DAY(ptr);
		d->hour = PyDateTime_DATE_GET_HOUR(ptr);
		d->minute = PyDateTime_DATE_GET_MINUTE(ptr);
		d->second = PyDateTime_DATE_GET_SECOND(ptr);
		// map microsecond precision to SQL nanosecond precision
		d->fraction = PyDateTime_DATE_GET_MICROSECOND(ptr) * 1000;

		destination.indicator = sizeof(SQL_TIMESTAMP_STRUCT);
	}

}


python_parameter_info determine_parameter_type(pybind11::object const & value)
{
//	{
//		boost::python::extract<long> extractor(value);
//		if (extractor.check()) {
//			return {set_integer, type_code::integer, size_not_important};
//		}
//	}
//	{
//		boost::python::extract<double> extractor(value);
//		if (extractor.check()) {
//			return {set_floating_point, type_code::floating_point, size_not_important};
//		}
//	}
//	{
//		boost::python::extract<std::string> extractor(value);
//		if (extractor.check()) {
//			auto const temp = extractor();
//			return {set_string, type_code::string, temp.size()};
//		}
//	}
//
//	auto ptr = value.ptr();
//	if (PyDateTime_Check(ptr)) {
//		return {set_timestamp, type_code::timestamp, size_not_important};
//	}
//
//	if (PyDate_Check(ptr)) {
//		return {set_date, type_code::date, size_not_important};
//	}
//
//	throw std::runtime_error("Could not convert python value to C++");
	throw std::runtime_error("You need to do something here!");
}


}