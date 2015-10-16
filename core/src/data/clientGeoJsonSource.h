#pragma once

#include "dataSource.h"
#include "data/tileData.h"

namespace mapbox {
namespace util {
namespace geojsonvt {
class GeoJSONVT;
class TilePoint;
class ProjectedFeature;
}}}

namespace Tangram {

using GeoJSONVT = mapbox::util::geojsonvt::GeoJSONVT;

class ClientGeoJsonSource : public DataSource {

public:

    ClientGeoJsonSource(const std::string& _name, const std::string& _url);
    ~ClientGeoJsonSource();

    void addData(const std::string& _data);
    void addPoint(double* _coords);
    void addLine(double* _coords, int _lineLength);
    void addPoly(double* _coords, int* _ringLengths, int rings);

    virtual bool loadTileData(std::shared_ptr<TileTask>&& _task, TileTaskCb _cb) override;
    virtual bool getTileData(std::shared_ptr<TileTask>& _task) override;
    virtual void cancelLoadingTile(const TileID& _tile) override {};
    virtual void clearData() override;

protected:

    virtual std::shared_ptr<TileData> parse(const Tile& _tile, std::vector<char>& _rawData) const override;

    // Transform a geojsonvt::TilePoint into the corresponding Tangram::Point
    Point transformPoint(mapbox::util::geojsonvt::TilePoint pt) const;

    std::unique_ptr<GeoJSONVT> m_store;
    std::vector<mapbox::util::geojsonvt::ProjectedFeature> m_features;

};

}
