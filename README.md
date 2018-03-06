# tiny-NDVI

Tools and techniques used:

C++, Qt, OpenCV, multi-threading, pixel manipulation, USGS EarthExplorer for test data

A desktop application to produce NDVI images from satellite images

Normalized Difference Vegetative Index (NDVI) is a method of determining the overall plant coverage over a given area through processing of satellite images. NDVI leverages the fact that green plants reflect a large amount (> 50%) of near-infrared radiation (NIR) but a small amount (<10%) of red wavelength radiation. Because this is a normalized index, NDVI values always fall between -1 and +1, with values approacgin +1 meaning an area is fully saturated with greenery and values approaching -1 being bare earth, snow or something else that is very reflective.

Mathematically, NDVI is defined as:   NDVI = (NIR-Red)/(NIR+Red)

This application provides a simple means of generating an NDVI image from two satellite images - one taken in the red wavelengths, and one taken in the NIR wavelengths. These images can be obtained from a number of sources, but in my opinion, USGS EarthExplorer is the best source.

Eventually, I want to add a number of features, including:

Batching of images together to create sets for particular purposes, fore example to see the NDVI of a particular sight over the course of seasons or years

Satellite metadata loading and checking
  - basically make sure the input images are the valid wavelength and from a satellite that senses in the right wavelengths

Ability to calculate normalized difference water index (NDWI) and lay this over the NDVI image so that water features are clearly distinguished

Customizable NDVI color ranges

Better image quality 
  - aspect, better contrast, etc.
