#pragma once

#include <boost/array.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <map>
#include <vector>
#include <agg_color_rgba.h>
#include "common.hpp"

struct GradientStop
{
  GradientStop()
    : color_(0, 0, 0)
  {}

  double offset_;
  agg::rgba8 color_;
};

typedef std::vector<GradientStop> GradientStops;

struct GradientBase
{
  enum SpreadMethod { spreadPad, spreadReflect, spreadRepeat };

  GradientBase()
    : spreadMethod_(spreadPad)
  {}

  boost::optional<boost::array<double, 6> > matrix_;
  SpreadMethod spreadMethod_;
  GradientStops stops_;
};

struct LinearGradient: GradientBase
{
  LinearGradient()
    : x1_(0)
    , y1_(0)
    , x2_(1)
    , y2_(0)
  {}

  double x1_, y1_, x2_, y2_;
};

struct RadialGradient: GradientBase
{
  RadialGradient()
    : cx_(0.5)
    , cy_(0.5)
    , r_(0.5)
  {}

  double cx_, cy_, r_, fx_, fy_;
};

typedef boost::variant<LinearGradient, RadialGradient> Gradient;

class Gradients
{
public:
  Gradients(XMLDocument & xml_document)
    : xml_document_(xml_document)
  {}

  boost::optional<Gradient> get(
    svg_string_t const & id/*, 
    length_factory_t const &, 
    get_bounding_box_func_t const & get_bounding_box*/);

private:
  XMLDocument & xml_document_;
};