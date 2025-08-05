#include "GlobalDataFactory.h"
#include "DataCenter/FrameAppData.h"

Core::FITKAbstractDataObject *GlobalDataFactory::createMeshData()
{
    return nullptr;
}

Core::FITKAbstractDataObject* GlobalDataFactory::createGeoData()
{
    // 创建几何数据
    return nullptr;
}

Core::FITKAbstractDataObject *GlobalDataFactory::createPhysicsData()
{
    // 创建abaqus数据
    return nullptr;
}

Core::FITKAbstractDataObject *GlobalDataFactory::createPostData()
{
    // 创建后处理数据
    return nullptr;
}

QHash<int, Core::FITKAbstractDataObject *> GlobalDataFactory::createOtherData()
{
    /// create application data
    QHash<int, Core::FITKAbstractDataObject *> other;
    Data::FrameAppData * appData = new Data::FrameAppData();
    other.insert(FRAME_APP_DATA_ID, appData);
    return other;
}
