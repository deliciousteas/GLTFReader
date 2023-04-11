#include "CesiumGltfReader/GltfReader.h"

#include <CesiumGltf/AccessorView.h>
#include <CesiumGltf/ExtensionCesiumRTC.h>
#include <CesiumGltf/ExtensionKhrDracoMeshCompression.h>

#include <catch2/catch.hpp>
#include <glm/vec3.hpp>
#include <gsl/span>
#include <rapidjson/reader.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace CesiumGltf;
using namespace CesiumGltfReader;
using namespace CesiumUtility;
using namespace std;
using namespace rapidjson;

namespace {
std::vector<std::byte> readFile(const std::filesystem::path& fileName) {
  std::ifstream file(fileName, std::ios::binary | std::ios::ate);
  REQUIRE(file);

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<std::byte> buffer(static_cast<size_t>(size));
  file.read(reinterpret_cast<char*>(buffer.data()), size);

  return buffer;
}
} // namespace


//对函数进行前项声明
void PrintfNamedObject(Model& model, NamedObject& nameObject);
void PrintfExtensibleObject(Model& model, ExtensibleObject& extensibleObject);
void PrintfModel(Model& model);
void PrintfScene(Model& model, Scene& scene);
void PrintfNode(Model& model, Node& node);
void PrintCamera(Model& model, Camera& camera);
void PrintfSkin(Model& model, Skin& skin);
void PrintfAnimation(Model& model, Animation& animation);
void PrintfAnimationChannel(Model& model, Animation& animation, AnimationChannel& animationchannel);
void PrintfAnimationSampler(Model& model, Animation& animation, AnimationSampler& animationsampler);
void PrintfMesh(Model& model, Mesh& mesh);
void PrintfMeshPrimitive(Model& model, MeshPrimitive& meshPrimitive);
void PrintfAccessor(Model& model, Accessor& accessor);
void PrintfBufferView(Model& model, BufferView& bufferview, int ctype, std::string type);
void PrintfBuffer(Model& model, Buffer& buffer);
void PrintfMaterial(Model& model, Material& material);




void PrintfMOccTextureInfo(Model& model, MaterialOcclusionTextureInfo& MOccTextureInfo) {
  ////一个控制遮挡的乘数
  //double strength = 1;
  //::TextureInfo
  if (MOccTextureInfo.strength = -1)
  {

    std::cout << "  strength为空" << std::endl;
  }
  else
  {
    std::cout << "  材质控制遮挡的乘数: " << MOccTextureInfo.strength << std::endl;
  }
}
void PrintfMNormalTextureInfo(Model& model, MaterialNormalTextureInfo& MNormalTextureInfo) {
  ////应用于纹理的每个法向量的标量参数
  //double scale = 1;
  
   std::cout << "  纹理的每个法向量的标量参数: " << MNormalTextureInfo.scale << std::endl;
  
}
void PrintfemissiveTexture(Model& model, TextureInfo& emissiveTexture) {}
void PrintfMPBRRoughness(Model& model, MaterialPBRMetallicRoughness& MPBRRoughness) {
  ////材质底色采样的乘数
  //std::vector<double> baseColorFactor = { 1, 1, 1, 1 };

  ////底色的纹理
  //std::optional<CesiumGltf::TextureInfo> baseColorTexture;

  ////材质金属度采样的乘数
  //double metallicFactor = 1;

  ////材质粗糙度的乘数
  //double roughnessFactor = 1;

  ////金属粗糙度的纹理
  //std::optional<CesiumGltf::TextureInfo> metallicRoughnessTexture;
  std::cout << "materialPBRMetallicRoughness begin: " << std::endl;
  PrintfExtensibleObject(model, MPBRRoughness);
  if (MPBRRoughness.baseColorFactor.begin() == MPBRRoughness.baseColorFactor.end())
  {
    std::cout << std::endl;
    std::cout << "  baseColorFactor为空" << std::endl;
  }
  else if (MPBRRoughness.baseColorFactor.begin() != MPBRRoughness.baseColorFactor.end())
  {
    
    std::cout << "  材质底色采样的乘数: ";
    for (int i = 0; i < MPBRRoughness.baseColorFactor.size(); ++i)
    {
      std::cout << MPBRRoughness.baseColorFactor[i] << " ";
    }
    std::cout << std::endl;
  }
  // metallicFactor
  if (MPBRRoughness.metallicFactor = -1)
  {
    
    std::cout << "  metallicFactor为空" << std::endl;
  }
  else 
  {
    std::cout << "  材质金属度采样的乘数: " << MPBRRoughness.metallicFactor << std::endl;
  }
  // roughnessFactor
  if (MPBRRoughness.roughnessFactor = -1)
  {

    std::cout << "  roughnessFactor为空" << std::endl;
  }
  else
  {
    std::cout << "  材质金属度采样的乘数: " << MPBRRoughness.roughnessFactor << std::endl;
  }
}
void PrintfMaterial(Model& model, Material& material) {
 //   //用于定义材质的金属粗糙度 
 //   std::optional<CesiumGltf::MaterialPBRMetallicRoughness> pbrMetallicRoughness;

 // //切线空间的法线纹理
 // std::optional<CesiumGltf::MaterialNormalTextureInfo> normalTexture;

 ////遮挡值是从R通道线性采样的,较高的值表示完全接受间接照明的区域，较低的数值表示没有间接光照。
 // std::optional<CesiumGltf::MaterialOcclusionTextureInfo> occlusionTexture;

 // //它控制了由材料发出的光的颜色和强度
 // std::optional<CesiumGltf::TextureInfo> emissiveTexture;

 // //这个值定义了发射型纹理的采样文本的线性乘数
 // std::vector<double> emissiveFactor = { 0, 0, 0 };

 // //材料的alpha渲染模式
 // std::string alphaMode = AlphaMode::OPAQUE;

 // //材料α的阈值。定义在`MASK`alpha模式下的阈值。如果alpha值大于或等于这个值，那么它将被渲染成完全不透明，否则，它被渲染为完全透明。一个值大于大于 "1.0 "将使整个材质呈现为完全透明。这个值在其他alpha模式下被忽略。
 // double alphaCutoff = 0.5;

 // //指定材料是否是双面的。当此值为false时，启用背面裁剪。当此值为true时，背面裁剪被禁用，双面照明被启用。
 // bool doubleSided = false;
  std::cout << "material begin: " << std::endl;
  PrintfNamedObject(model, material);
  //用于定义材质的金属粗糙度 
  std::optional<CesiumGltf::MaterialPBRMetallicRoughness> pbrMetallicRoughness;
  if (material.pbrMetallicRoughness.has_value())
  {
    MaterialPBRMetallicRoughness& MPBRRoughness = material.pbrMetallicRoughness.value();
    PrintfMPBRRoughness(model, MPBRRoughness);
  }
  else {
    std::cout << "  there is no Material PBRMetallicRoughness" << std::endl;
  }
  //切线空间的法线纹理
  std::optional<CesiumGltf::MaterialNormalTextureInfo> normalTexture;
  if (material.normalTexture.has_value())
  {
    MaterialNormalTextureInfo& MNormalTextureInfo = material.normalTexture.value();
    PrintfMNormalTextureInfo(model, MNormalTextureInfo);
  }
  else {
    std::cout << "  there is no Material NormalTextureInfo" << std::endl;
  }
  ////遮挡值是从R通道线性采样的,较高的值表示完全接受间接照明的区域，较低的数值表示没有间接光照。
  std::optional<CesiumGltf::MaterialOcclusionTextureInfo> occlusionTexture;
  if (material.occlusionTexture.has_value())
  {
   /* MaterialNormalTextureInfo& MOccTextureInfo = material.occlusionTexture.value();
    PrintfMOccTextureInfo(model, MOccTextureInfo);*/
  }
  else {
    std::cout << "  there is no Material OcclusionTextureInfo" << std::endl;
  }

 // //它控制了由材料发出的光的颜色和强度
  std::optional<CesiumGltf::TextureInfo> emissiveTexture;
  if (material.emissiveTexture.has_value())
  {
    TextureInfo& emissiveTexture = material.emissiveTexture.value();
    PrintfemissiveTexture(model, emissiveTexture);
  }
  else {
    std::cout << "  there is no emissiveTexture" << std::endl;
  }
  //这个值定义了发射型纹理的采样文本的线性乘数
// std::vector<double> emissiveFactor = { 0, 0, 0 };

// //材料的alpha渲染模式
  //std::string alphaMode = AlphaMode::OPAQUE;
   if (material.alphaMode.empty())
   {
     std::cout << "  there is no alphaMode" << std::endl;
   }
   else if(material.alphaMode == Material::AlphaMode::OPAQUE)
   {
     std::cout << "  alphaMode: OPAQUE  材质的alpha值被忽略，渲染后是完全不透明的"<<std::endl;
   }
   else if (material.alphaMode == Material::AlphaMode::BLEND)
   {
     std::cout << "  alphaMode: blend   alpha值用于合成源区和目标区。渲染后的输出与背景使用正常的绘画操作相结合"<<std::endl;
   }
   else if (material.alphaMode == Material::AlphaMode::MASK)
   {
     std::cout << "  alphaMode: mask 渲染后的输出是完全不透明的，或者是完全透明的，具体取决于alpha值和指定的alphaCutoff值"<<std::endl;
     std::cout<<"  alphaCutoff = " << material.alphaCutoff << " 此值只在mask模型下被定义" << std::endl;
   }

// //指定材料是否是双面的。当此值为false时，启用背面裁剪。当此值为true时，背面裁剪被禁用，双面照明被启用。
   //bool doubleSided = false;
   if (material.doubleSided = false)
   {
     std::cout << "  材质启用背面裁剪" << std::endl;
   }
   else {
     std::cout << "  材质为双面，背面裁剪被禁用，双面照明开启" << std::endl;
   }
}
void PrintfBuffer(Model& model, Buffer& buffer) {


  std::cout << "buffer begin: " << std::endl;
  PrintfNamedObject(model, buffer);
  std::cout << "  Buffer ByteLengeh:" << buffer.byteLength << " 字节"<<std::endl;
  if (buffer.uri.has_value())
  {
    std::cout << "  Buffer URI: " << buffer.uri.value() << std::endl;
  }
  else {
    std::cout << "  there is no buffer uri" << std::endl;
  }

  
}
void PrintfBufferView(Model& model,BufferView& bufferview,int ctype,std::string type, int count, int byteOffset)
{
 // //buffer的索引
 // int32_t buffer = -1;

 // //相对于buffer的偏移
 // int64_t byteOffset = 0;

 // //bufferview的字节长度
 // int64_t byteLength = int64_t();

 // //当两个以上accessor使用一个bufferview时，步长必须被定义
 // std::optional<int64_t> byteStride;

 ////要使用的GPU缓冲区类型？
 // std::optional<int32_t> target;


  std::cout << "bufferview begin: " << std::endl;
  PrintfNamedObject(model, bufferview);
  // buffer
  int bufferIndex = bufferview.buffer;
  Buffer& buffer = model.buffers[bufferIndex];

  // glb的写法
  if (!buffer.uri.has_value()) {
    //则证明其为glb,另一种写法
    std::cout << "其为glb文件" << std::endl;
    return;
  } else {

    ////read bin file
    //= buffer.cesium.data;
    std::vector<std::byte> exLinkbuffer = readFile("D:\\gltfmodel\\tesla_2018_model_3\\scene.bin");

    //按位置偏移取buffer
    

    //先看buffer的数据类型，即vec3/vec2/sclar
    int typeLength;
    if (type == Accessor::Type::SCALAR) {
      typeLength = 1;
      std::cout << "  Accessor Type = scalar" << std::endl;
    } else if (type == Accessor::Type::VEC3) {
      typeLength = 3;
      std::cout << "  Accessor Type = VEC3" << std::endl;
    } else if (type == Accessor::Type::VEC2) {
      typeLength = 2;
      std::cout << "  Accessor Type = VEC2" << std::endl;
    }

    //再看buffer的数据要素类型，即 5120 BYTE 5121 UNSIGNED_BYTE 5122 SHORT 5123
    // UNSIGNED_SHORT 5125 UNSIGNED_INT 5126 FLOAT
    int ctypeLength;
    if (ctype == Accessor::ComponentType::BYTE) {
      ctypeLength = 1;
      std::cout << "  Accessor componentType = byte" << std::endl;
    } else if (ctype == Accessor::ComponentType::FLOAT) {
      ctypeLength = 4;
      std::cout << "  Accessor componentType = float" << std::endl;
    } else if (ctype == Accessor::ComponentType::UNSIGNED_BYTE) {
      ctypeLength = 1;
      std::cout << "  Accessor componentType = unsigned byte" << std::endl;
    } else if (ctype == Accessor::ComponentType::SHORT) {
      ctypeLength = 2;
      std::cout << "  Accessor componentType = short" << std::endl;
    } else if (ctype == Accessor::ComponentType::UNSIGNED_SHORT) {
      ctypeLength = 2;
      std::cout << "  Accessor componentType = unsigned short" << std::endl;
    } else if (ctype == Accessor::ComponentType::UNSIGNED_INT) {
      ctypeLength = 4;
      std::cout << "  Accessor componentType = unsigned int" << std::endl;
    }
    //byteoffest
    int bufferViewByteOffset = bufferview.byteOffset;
    if (bufferViewByteOffset != -1) {
      std::cout << "  Bufferview相对于buffer偏移了: " << bufferViewByteOffset <<" 字节" <<std::endl;
    }
    else {
      std::cout << "  there is no ByteOffset "  << std::endl;
    }
    //byteLength
    int bufferLength = bufferview.byteLength;
    std::cout << "  bufferview的长度为: " << bufferLength << " 字节" <<std::endl;
    //// byteStride std::optional<int64_t> byteStride;
    if (bufferview.byteStride.has_value()) {
  
      std::cout << "  步长为:" << bufferview.byteStride.value() << "字节"<< std::endl;
    }
    else {
      std::cout << "  there is no byteStride" << std::endl;
    }


    //----------计算该段要素的内存长度----------
   // int componentByteLength = componentNum * typeLength * ctypeLength;

    //是否有步长
    int componentByteStride = bufferview.byteStride.value();
    //取到该buffer

   // std::byte* bufferStart = (std::byte*)exLinkbuffer[bufferViewByteOffset + componentByteStride];

    int currentBufLoc = bufferViewByteOffset;
    int currentBufEndLoc = currentBufLoc + bufferview.byteLength;
    int count = 1;
    while (currentBufLoc + componentByteStride <= currentBufEndLoc&& count<5) {

      // x
      std::byte floatValue[4];
      floatValue[0] = exLinkbuffer[currentBufLoc + 0];
      floatValue[1] = exLinkbuffer[currentBufLoc + 1];
      floatValue[2] = exLinkbuffer[currentBufLoc + 2];
      floatValue[3] = exLinkbuffer[currentBufLoc + 3];
      float P_x = *((float*)floatValue);
      //y
      floatValue[0] = exLinkbuffer[currentBufLoc + 4 + 0];
      floatValue[1] = exLinkbuffer[currentBufLoc + 4 + 1];
      floatValue[2] = exLinkbuffer[currentBufLoc + 4 + 2];
      floatValue[3] = exLinkbuffer[currentBufLoc + 4 + 3];
      float P_y = *((float*)floatValue);
      //z
      floatValue[0] = exLinkbuffer[currentBufLoc + 8 + 0];
      floatValue[1] = exLinkbuffer[currentBufLoc + 8 + 1];
      floatValue[2] = exLinkbuffer[currentBufLoc + 8 + 2];
      floatValue[3] = exLinkbuffer[currentBufLoc + 8 + 3];
      float P_z = *((float*)floatValue);
      std::cout << "  已读取" << count << " 个点  " <<std::endl;

      std::cout << "  postion :" << P_x << "  " << P_y << "  " << P_z << std::endl;
      count++;
      currentBufLoc += componentByteStride;
    }
    int buffers = bufferview.buffer;
    Buffer& buffer = model.buffers[buffers];
    PrintfBuffer(model,buffer);
  }
    
  
}
void PrintfAccessor(Model& model, Accessor& accessor ) {
  //
  /////bufferview的索引
  //int32_t bufferView = -1;

  ////相对bufferview的偏移，以字节为单位
  //int64_t byteOffset = 0;

  ////accessor component 的数据类型
  //int32_t componentType = ComponentType::BYTE;

  ////指定在使用前是否对整数数据值进行标准化处理,[0, 1] (for unsigned types) or to [-1, 1](for signed types)
  //bool normalized = false;

  ////accessor引用的元素的数量
  //int64_t count = int64_t();

  ////accessor元素的类型
  //std::string type = Type::SCALAR;

  ////accessor中每个元素的最大值，max 和min数组长度相同
  //std::vector<double> max;

  ////accessor中每个元素的最小值，稀疏访问？
  //std::vector<double> min;

  ////稀疏存储
  //std::optional<CesiumGltf::AccessorSparse> sparse;
  std::cout << "accessor begin: " << std::endl;
  PrintfNamedObject(model, accessor);
  
  int accessorCountIndex = accessor.count;
  std::cout << "  Accessor Count = " << accessorCountIndex << std::endl;
  
  //输出 accessor max min
  std::vector<double> accessorMax = accessor.max;
  if (accessorMax.begin() == accessorMax.end())
  {
    std::cout << std::endl;
    std::cout << "  accessor最大值为空" << std::endl;
  }
  else if (accessorMax.begin() != accessorMax.end())
  {
    std::cout << std::endl;
    std::cout << "  Accessor Max: ";
    for (int i = 0; i < accessorMax.size(); ++i)
    {
      std::cout << accessorMax[i] << " ";
    }
    std::cout << std::endl;
  }
  std::vector<double> accessorMin = accessor.min;
  if (accessorMin.begin() == accessorMin.end())
  {
    std::cout << std::endl;
    std::cout << "  accessor最小值为空" << std::endl;
  }
  else if (accessorMin.begin() != accessorMin.end())
  {
    std::cout << std::endl;
    std::cout << "  Accessor Min: ";
    for (int i = 0; i < accessorMin.size(); ++i)
    {
      std::cout << accessorMin[i] << " " ;
    }
    std::cout << std::endl;
  }
  //accessor normalized
  bool accessorNormalizes = accessor.normalized;
  if (accessorNormalizes = false) {
    std::cout << "  无归一化" << std::endl;
  } else {
    std::cout << "  已归一化" << std::endl;
  }
  ////buyeoffset 相对于起始bufferview的偏移，一定是componenttype中占字节数的倍数?
  //int accessorbyteOffset = accessor.byteOffset;
  //std::cout << "  accessor byte offset: " << accessorbyteOffset << std::endl;

  // bufferview 
  int bufferviewIndex = accessor.bufferView;
  BufferView& bufferview = model.bufferViews[bufferviewIndex];
  PrintfBufferView(model, bufferview, accessor.componentType, accessor.type, accessor.count, accessor.byteOffset);


}

void PrintfBufferView(Model& model, BufferView& bufferview, int ctype, std::string type)
{
}

void PrintfMeshPrimitive(Model& model, MeshPrimitive& meshPrimitive) {

  ////一个JSON对象，其中每个键对应的是一个mesh属性语义，每个值是包含属性数据的accessor的索引。
  //std::unordered_map<std::string, int32_t> attributes;

  ////accessor的索引，也是mesh顶点的索引，当被定义时，一定会出现SCALAR type 和 unsigned integer component type.
 
  //int32_t indices = -1;

  ////material 的索引
  //int32_t material = -1;
  ////primitive的拓扑类型，0 POINTS  1 LINES  2 LINE_LOOP  3 LINE_STRIP  4 TRIANGLE   5 TRIANGLE_STRIP   6 TRIANGLE_FAN  一般是4三角网
  //int32_t mode = Mode::TRIANGLES;
  ////关于 morphology target 的数组？？
  //std::vector<std::unordered_map<std::string, int32_t>> targets;
  std::cout << "mesh primitive begin: " << std::endl;
  PrintfExtensibleObject(model, meshPrimitive);
  // attributes: accessor
  //std::unordered_map<std::string, int32_t> attributes;

  std::cout << "  Mesh Primitive Attributes: " << std::endl;
  for (auto iter = meshPrimitive.attributes.begin(); iter != meshPrimitive.attributes.end(); ++iter) {
    std::string key = iter->first;
    std::int32_t value = iter->second;
   
    std::cout << "  Key: " << key << "  ,  Value: " << value << endl;

  }
  // Mode
  int primitiveModeIndex = meshPrimitive.mode;
  if (primitiveModeIndex = 4) {
    std::cout << "  Primitive Mode =  TRIANGLES" << std::endl;
  }
  else {
    std::cout << "  Primitive Mode is  not  TRIANGLES" << std::endl;
  }

 
  // material: materials
  int materialIndex = meshPrimitive.material;
  Material& material = model.materials[materialIndex];
  PrintfMaterial(model,material);


 
  // position accessor
  int positionAccessorIndex = meshPrimitive.attributes["POSITION"];
  Accessor& positionAccessor = model.accessors[positionAccessorIndex];
  PrintfAccessor(model, positionAccessor);
  
 // int normalAccessorIndex = meshPrimitive.attributes["NORMAL"];
 // Accessor& normalAccessor = model.accessors[normalAccessorIndex];
 // PrintfAccessor(model, normalAccessor);

 // int texcoordAccessorIndex = meshPrimitive.attributes["TEXCOORD"];
 // Accessor& texcoordAccessor = model.accessors[texcoordAccessorIndex];
 // PrintfAccessor(model, texcoordAccessor);
 //  ////indices: accessor
 //int primitiveIndex = meshPrimitive.indices;
 // Accessor& accessor = model.accessors[primitiveIndex];
 // PrintfAccessor(model, accessor);
 // 
}
void PrintfMesh(Model& model, Mesh& mesh) {
  ////primitive的数组，定义了几何，
  //std::vector<CesiumGltf::MeshPrimitive> primitives;

  ////应用于变形目标的权重数组，数组里的元素数量 = 目标数
  //std::vector<double> weights;

  std::cout << "Mesh begin: " << std::endl;
  PrintfNamedObject(model, mesh);
  std::vector<double> meshWeight = mesh.weights;
  if (meshWeight.begin() == meshWeight.end())
  {
    std::cout << "  Mesh Weight数组为空" << std::endl;
  }
  else if (meshWeight.begin() != meshWeight.end())
  {
    std::cout << "  MeshWeight: ";
    for (auto itre = meshWeight.begin(); itre != meshWeight.end(); ++itre) {
      std::cout << *itre << " ";
    }
    std::cout << std::endl;
  }
  
  for (int i = 0; i < mesh.primitives.size(); i++) {
    MeshPrimitive& meshPrimitive = mesh.primitives[i];
    PrintfMeshPrimitive(model, meshPrimitive);
  }

}

void PrintfAnimationSampler(Model&model,Animation& animation, AnimationSampler& animationsampler) {
  ///accessor的索引，包括关键帧的时间戳
  //  int32_t input = -1;
  //插值方法

  //std::string interpolation = Interpolation::LINEAR;

  //accessor的索引，包括关键帧的输出值
  //int32_t output = -1;
  PrintfExtensibleObject(model, animationsampler);
  std::cout << "animation sampler begin:" << std::endl;
  std::cout << "  Animation Sampler Input： " << animationsampler.input<< std::endl;
  std::cout << "  Animation Sampler Output： " << animationsampler.output << std::endl;
  string animationSamplerInterpolation = animationsampler.interpolation;
  if (animationSamplerInterpolation.empty()) {
    std::cout << "  there is no AnimationSampler Interpolation" << std::endl;
  }
  //可以再写细一点，把插值类型解释一下
  else {
    std::cout << "  动画使用的插值算法为： " << animationSamplerInterpolation << std::endl;
  }

}
void PrintfAnimationChannel(Model& model, Animation& animation, AnimationChannel&animationchannel) {
  //int32_t sampler = -1;

  //CesiumGltf::AnimationChannelTarget target;
  PrintfExtensibleObject(model,  animationchannel);
  std::cout << "animation channel begin:" << std::endl;
  std::cout << "  采样器的索引为： " << animationchannel.sampler << std::endl;
  /*int animationchannelsamperIndex = animation.samplers;
  Sampler& sampler = animationchannel.sampler[animationchannelsamperIndex];
  PrintfSampler();*/
  int animationchannelTargetNode = animationchannel.target.node;
  string animationChannelTargetPath = animationchannel.target.path;
  if (animationchannelTargetNode != -1) {
    std::cout << "  要做动画的node的索引： " << animationchannelTargetNode << std::endl;
    std::cout << "  TRS属性的名称为： " << animationChannelTargetPath << std::endl;
  }
  else {
    std::cout << "  there is no Animationchannel Target Node" << std::endl;
  }


}
void PrintfAnimation(Model& model, Animation& animation) {
  ///**
  // *animation channel（动画数据的“源（source）”连接到“目标target”的通道，与target一一对应） 的数组
  // */
  //std::vector<CesiumGltf::AnimationChannel> channels;

  ///**
  // 一个动画采样器的数组。一个动画采样器将时间戳与一连串的输出值结合起来，并定义了一个插值算法.
  // */
  //std::vector<CesiumGltf::AnimationSampler> samplers;
  std::cout << "animation begin:" << std::endl;
  PrintfNamedObject(model, animation);
  if (animation.channels.begin() != animation.channels.end()) {
    for (int i = 0; i < animation.channels.size(); ++i) {
      AnimationChannel& animationchannel = animation.channels[i];
      PrintfAnimationChannel(model,animation, animationchannel);
    }
  }
  else {
    std::cout << "  error:Animation has no channel" << std::endl;
  }
  if (animation.samplers.begin() != animation.samplers.end()) {
    for (int i = 0; i < animation.samplers.size(); ++i) {
      AnimationSampler& animationsampler = animation.samplers[i];
      PrintfAnimationSampler(model,animation, animationsampler);
    }
  }
  else {
    std::cout << "  error:Animation has no sampler" << std::endl;
  }

}

void PrintfSkin(Model& model, Skin& skin) {
  std::cout << "skin begin:" << std::endl;
  PrintfNamedObject(model, skin);
  /*

   int32_t inverseBindMatrices = -1;
  int32_t skeleton = -1;
  std::vector<int32_t> joints;

  */

}

void PrintCamera(Model& model, Camera& camera) {

 // //camera结构里有一个type结构
 // struct Type {
 //   inline static const std::string perspective = "perspective";

 //   inline static const std::string orthographic = "orthographic";
 // };

 // //正交投影会创建一个正交矩阵，和透视矩阵不能同时被定义
 // std::optional<CesiumGltf::CameraOrthographic> orthographic;

 // //透视投影
 // std::optional<CesiumGltf::CameraPerspective> perspective;

 ////用来判断是什么投影
 // std::string type = Type::perspective;


  std::cout << "camera begin: " << std::endl;
  PrintfNamedObject(model, camera);
 
  std::string cameraType = camera.type;
  std::cout << "  Camera Type: " << cameraType << std::endl;

  if (camera.orthographic.has_value()) {
    CameraOrthographic cameraorthographic = camera.orthographic.value();
    std::cout << "  X轴上投影的放大倍数: " <<cameraorthographic.xmag << std::endl;
    std::cout << "  Y轴上投影的放大倍数: " << cameraorthographic.ymag<< std::endl;
    std::cout << "  距离远裁切面的距离： " << cameraorthographic.zfar << std::endl;
    std::cout << "  距离近裁切面的距离： " << cameraorthographic.znear << std::endl;
  }
  else {
    std::cout << "  相机没有使用正交投影" << std::endl;
  }
  if (camera.perspective.has_value()) {
    CameraPerspective cameraperspective = camera.perspective.value();
    std::cout << "  相机视锥体的顶角: " << cameraperspective.yfov <<"°" <<std::endl;
    std::cout << "  距离近裁切面的距离： " << cameraperspective.znear << std::endl;
    if (cameraperspective.zfar.has_value()) {
      std::cout << "  距离远裁切面的距离： " << cameraperspective.zfar.value() << std::endl;
    }
    else {
      std::cout << "透视投影没有存储距离远裁切面的距离的属性" << std::endl;
    }
    if (cameraperspective.aspectRatio.has_value()) {
      std::cout << "  透视投影中屏幕长宽比为： " << cameraperspective.aspectRatio.value() << std::endl;
    }
    else {
      std::cout << "透视投影没有存储屏幕长宽比的属性" << std::endl;
    }
  }
  else {
    std::cout << "  相机没有使用透视投影" << std::endl;
  }


}

void PrintfNode(Model& model, Node& node) {
  //int32_t camera = -1;
  //std::vector<int32_t> children;
  //int32_t skin = -1;
  ////4*4的数组
  //std::vector<double> matrix = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
  //int32_t mesh = -1;
  ////旋转矩阵（x,y,z,w）
  //std::vector<double> rotation = { 0, 0, 0, 1 };
  ////旋转矩阵(x,y,z)的缩放矩阵
  //std::vector<double> scale = { 1, 1, 1 };
  ////平移矩阵
  //std::vector<double> translation = { 0, 0, 0 };
  ////实例化相关，数组的数量与引用的mesh数量相同
  //std::vector<double> weights;

  std::cout << "node begin: "<< std::endl;
  PrintfNamedObject(model,node);
  
  std::vector<double> nodeMatrix = node.matrix;
  if (nodeMatrix.begin() == nodeMatrix.end())
  {
    std::cout << "  NodeMatrix矩阵为空" << std::endl;
  }
  else if(nodeMatrix.begin() != nodeMatrix.end())
   {
      std::cout << "  NodeMatrix:";
      int index = 0;
      for (int i = 0; i < 4; ++i)
    {
      std::cout<<std::endl;
      for (int j = 0; j < 4; ++j)
     {
       std::cout << "  "<<nodeMatrix[index] << "  ";
        index++;
      }
     }
   }
  
  std::vector<double> nodeRotation = node.rotation;
  if (nodeRotation.begin() == nodeRotation.end())
  {
    std::cout << std::endl;
    std::cout << "  NodeRotation矩阵为空" << std::endl;
  }
  else if (nodeRotation.begin() != nodeRotation.end())
  {
    std::cout << std::endl;
    std::cout << "  NodeRotation:";
    for (int i = 0; i < nodeRotation.size(); ++i)
    {
      std::cout << nodeRotation[i] << " ";
    }
  }
  std::vector<double> nodeScale = node.scale;
  if (nodeScale.begin() == nodeScale.end())
  {
    std::cout << std::endl;
    std::cout << "  NodeScale矩阵为空" << std::endl;
  }
  else if (nodeScale.begin() != nodeScale.end())
  {
    std::cout << std::endl;
    std::cout << "  NodeScale:";
    for (int i = 0; i < nodeScale.size(); ++i)
    {
      std::cout << nodeScale[i] << " ";
    }
  }
  std::vector<double> nodeTranslation = node.translation;
  if (nodeTranslation.begin() == nodeTranslation.end())
  {
    std::cout << std::endl;
    std::cout << "  NodeTranslation矩阵为空" << std::endl;
  }
  else if (nodeTranslation.begin() != nodeTranslation.end())
  {
    std::cout << std::endl;
    std::cout << "  NodeTranslation:";
    for (int i = 0; i < nodeTranslation.size(); ++i)
    {
      std::cout << nodeTranslation[i] << " ";
    }
  }
  std::vector<double> nodeWeights = node.weights;
  if (nodeWeights.begin() == nodeWeights.end())
  {
    std::cout << std::endl;
    std::cout << "  NodeWeights矩阵为空" << std::endl;
  }
  else if (nodeWeights.begin() != nodeWeights.end())
  {
    std::cout << std::endl;
    std::cout << "  nodeWeights:";
    for (int i = 0; i < nodeWeights.size(); ++i)
    {
      std::cout << nodeWeights[i] << " ";
    }
  }

  if (node.camera != -1) {
    int cameraIndex = node.camera;
    Camera& camera = model.cameras[cameraIndex];
    PrintCamera(model, camera);
  }
  else {
    std::cout << "  Node has no camera" << std::endl;
  }
  if (node.skin != -1) {
    int skinIndex = node.skin;
    Skin& skin = model.skins[skinIndex];
    PrintfSkin(model, skin);
  }
  else {
    std::cout << "  Node has no skin" << std::endl;
  }

  if (node.mesh != -1) {
    Mesh& mesh = model.meshes[node.mesh];
    PrintfMesh(model, mesh);
  }
  else {
    std::cout << "  Node has no mesh" << std::endl;
  }
 
  for (int i = 0; i < node.children.size(); ++i) {
    int nodeIndex = node.children[i];
    Node& node = model.nodes[nodeIndex];
    PrintfNode(model, node);
  }
  
}

void PrintfScene(Model& model, Scene& scene) {
  std::cout << "scene begin:" << std::endl;
  PrintfNamedObject(model, scene);
  for (int i = 0; i < scene.nodes.size(); ++i) {
  Node& node = model.nodes[scene.nodes[i]];
  PrintfNode(model, node);
  }
  
}

void PrintfModel(Model& model) {
  std::cout << "model begin:" << std::endl;
  PrintfExtensibleObject(model,model);
  if (model.animations.begin() != model.animations.end()) {
    for (int i = 0; i < model.animations.size(); ++i) {
      Animation& animation = model.animations[i];
      PrintfAnimation(model, animation);
    }
  }
  else {
    std::cout << "  Model has no animation" << std::endl;
  }
  for (int i = 0; i < model.scenes.size(); ++i) {
  Scene& scene = model.scenes[i];
  PrintfScene(model, scene);
  }
  
}
void PrintfExtensibleObject(Model& model, ExtensibleObject& extensibleObject) {
  /*JsonValue::Object extras;
   std::unordered_map<std::string, std::any> extensions;*/

   //打印extension
  std::unordered_map<std::string, std::any> extensions;
  std::cout << "  Extensions: ";
  for (auto iter = extensions.begin(); iter != extensions.end(); ++iter) {
    std::string key = iter->first;
    std::any value = iter->second;
    
    std::cout << "  Key: " << key << "  ,  Value: ";

    // 根据值的类型使用 std::any_cast 进行转换并输出
    if (value.type() == typeid(std::string)) {
      std::cout << std::any_cast<std::string>(value);
    }
    else if (value.type() == typeid(int)) {
      std::cout << std::any_cast<int>(value);
    }
    else if (value.type() == typeid(double)) {
      std::cout << std::any_cast<double>(value);
    }
    else if (value.type() == typeid(bool)) {
      std::cout << std::boolalpha << std::any_cast<bool>(value);
    }
    else {
      std::cout << "  Unknown type";
    }

    std::cout << std::endl;
  }

  ////打印extra;
  JsonValue::Object extras;
  std::cout << std::endl;
  std::cout << "  Extra: ";
  for (auto& pair : extras) {
    std::cout << "  Key: " << pair.first << "  ,  Value: ";

   /* if (pair.second.isArray()) {
      std::cout << pair.second.getArray() << std::endl;
    }
    else if (pair.second.isBool()) {
      std::cout << (pair.second.getBool() ? "true" : "false") << std::endl;
    }
    else if (pair.second.isDouble()) {
      std::cout << pair.second.getDouble << std::endl;
    }
    else if (pair.second.isInt64()) {
      std::cout << pair.second.getInt64 << std::endl;
    }
    else if (pair.second.isNumber()) {
      std::cout << pair.second.getInt64 << std::endl;
    }
    else if (pair.second.isObject()) {
      std::cout << pair.second.getObject << std::endl;
    }
    else if (pair.second.isString()) {
      std::cout << pair.second.getString << std::endl;
    }
    else if (pair.second.isUint64()) {
      std::cout << pair.second.getUint64 << std::endl;
    }*/
  }
  std::cout << std::endl;
}

    
   


void PrintfNamedObject(Model& model, NamedObject& nameObject) {

  std::cout << "  name: " << nameObject.name << std::endl;
  PrintfExtensibleObject(model, nameObject);
  }

TEST_CASE("MyTest") {
  //读取.gltf文件
  std::vector<std::byte> buffer =readFile("D:\\gltfmodel\\tesla_2018_model_3\\scene.gltf");
  GltfReader reader;
  GltfReaderResult result = reader.readGltf(buffer);
  //读出model的值
  Model& model = result.model.value();
  PrintfModel(model);
}

TEST_CASE("CesiumGltfReader::GltfReader") {
  using namespace std::string_literals;

  std::string s = R"(
    {
      "accessors": [
        {
          "count": 4,
          "componentType": 5121,
          "type": "VEC2",
          "max": [
            1,
            2.2,
            3.3
          ],
          "min": [
            0,
            -1.2
          ]
        }
      ],
      "meshes": [
        {
          "primitives": [
            {
              "attributes": {
                "POSITION": 0,
                "NORMAL": 1
              },
              "targets": [
                {
                  "POSITION": 10,
                  "NORMAL": 11
                }
              ]
            }
          ]
        }
      ],
      "surprise": {
        "foo": true
      }
    }
  )";

  GltfReader reader;
  GltfReaderResult result = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()));
  CHECK(result.errors.empty());
  REQUIRE(result.model.has_value());

  Model& model = result.model.value();
  REQUIRE(model.accessors.size() == 1);
  CHECK(model.accessors[0].count == 4);
  CHECK(
      model.accessors[0].componentType ==
      Accessor::ComponentType::UNSIGNED_BYTE);
  CHECK(model.accessors[0].type == Accessor::Type::VEC2);
  REQUIRE(model.accessors[0].min.size() == 2);
  CHECK(model.accessors[0].min[0] == 0.0);
  CHECK(model.accessors[0].min[1] == -1.2);
  REQUIRE(model.accessors[0].max.size() == 3);
  CHECK(model.accessors[0].max[0] == 1.0);
  CHECK(model.accessors[0].max[1] == 2.2);
  CHECK(model.accessors[0].max[2] == 3.3);

  REQUIRE(model.meshes.size() == 1);
  REQUIRE(model.meshes[0].primitives.size() == 1);
  CHECK(model.meshes[0].primitives[0].attributes["POSITION"] == 0);
  CHECK(model.meshes[0].primitives[0].attributes["NORMAL"] == 1);

  REQUIRE(model.meshes[0].primitives[0].targets.size() == 1);
  CHECK(model.meshes[0].primitives[0].targets[0]["POSITION"] == 10);
  CHECK(model.meshes[0].primitives[0].targets[0]["NORMAL"] == 11);
}

TEST_CASE("Read TriangleWithoutIndices") {
  std::filesystem::path gltfFile = CesiumGltfReader_TEST_DATA_DIR;
  gltfFile /=
      "TriangleWithoutIndices/glTF-Embedded/TriangleWithoutIndices.gltf";
  std::vector<std::byte> data = readFile(gltfFile);
  GltfReader reader;
  GltfReaderResult result = reader.readGltf(data);
  REQUIRE(result.model);

  const Model& model = result.model.value();
  REQUIRE(model.meshes.size() == 1);
  REQUIRE(model.meshes[0].primitives.size() == 1);
  REQUIRE(model.meshes[0].primitives[0].attributes.size() == 1);
  REQUIRE(model.meshes[0].primitives[0].attributes.begin()->second == 0);

  AccessorView<glm::vec3> position(model, 0);
  REQUIRE(position.size() == 3);
  CHECK(position[0] == glm::vec3(0.0, 0.0, 0.0));
  CHECK(position[1] == glm::vec3(1.0, 0.0, 0.0));
  CHECK(position[2] == glm::vec3(0.0, 1.0, 0.0));
}

TEST_CASE("Nested extras deserializes properly") {
  const std::string s = R"(
    {
        "asset" : {
            "version" : "1.1"
        },
        "extras": {
            "A": "Hello World",
            "B": 1234567,
            "C": {
                "C1": {},
                "C2": [1,2,3,4,5]
            }
        }
    }
  )";

  GltfReader reader;
  GltfReaderResult result = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()));

  REQUIRE(result.errors.empty());
  REQUIRE(result.model.has_value());

  Model& model = result.model.value();
  auto cit = model.extras.find("C");
  REQUIRE(cit != model.extras.end());

  JsonValue* pC2 = cit->second.getValuePtrForKey("C2");
  REQUIRE(pC2 != nullptr);

  CHECK(pC2->isArray());
  std::vector<JsonValue>& array = std::get<std::vector<JsonValue>>(pC2->value);
  CHECK(array.size() == 5);
  CHECK(array[0].getSafeNumber<double>() == 1.0);
  CHECK(array[1].getSafeNumber<std::uint64_t>() == 2);
  CHECK(array[2].getSafeNumber<std::uint8_t>() == 3);
  CHECK(array[3].getSafeNumber<std::int16_t>() == 4);
  CHECK(array[4].getSafeNumber<std::int32_t>() == 5);
}

TEST_CASE("Can deserialize KHR_draco_mesh_compression") {
  const std::string s = R"(
    {
      "asset": {
        "version": "2.0"
      },
      "meshes": [
        {
          "primitives": [
            {
              "extensions": {
                "KHR_draco_mesh_compression": {
                  "bufferView": 1,
                  "attributes": {
                    "POSITION": 0
                  }
                }
              }
            }
          ]
        }
      ]
    }
  )";

  GltfReaderOptions options;
  GltfReader reader;
  GltfReaderResult result = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()),
      options);

  REQUIRE(result.errors.empty());
  REQUIRE(result.model.has_value());

  Model& model = result.model.value();
  REQUIRE(model.meshes.size() == 1);
  REQUIRE(model.meshes[0].primitives.size() == 1);

  MeshPrimitive& primitive = model.meshes[0].primitives[0];
  ExtensionKhrDracoMeshCompression* pDraco =
      primitive.getExtension<ExtensionKhrDracoMeshCompression>();
  REQUIRE(pDraco);

  CHECK(pDraco->bufferView == 1);
  CHECK(pDraco->attributes.size() == 1);

  REQUIRE(pDraco->attributes.find("POSITION") != pDraco->attributes.end());
  CHECK(pDraco->attributes.find("POSITION")->second == 0);

  // Repeat test but this time the extension should be deserialized as a
  // JsonValue.
  reader.getExtensions().setExtensionState(
      "KHR_draco_mesh_compression",
      CesiumJsonReader::ExtensionState::JsonOnly);

  GltfReaderResult result2 = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()),
      options);

  REQUIRE(result2.errors.empty());
  REQUIRE(result2.model.has_value());

  Model& model2 = result2.model.value();
  REQUIRE(model2.meshes.size() == 1);
  REQUIRE(model2.meshes[0].primitives.size() == 1);

  MeshPrimitive& primitive2 = model2.meshes[0].primitives[0];
  JsonValue* pDraco2 =
      primitive2.getGenericExtension("KHR_draco_mesh_compression");
  REQUIRE(pDraco2);

  REQUIRE(pDraco2->getValuePtrForKey("bufferView"));
  CHECK(
      pDraco2->getValuePtrForKey("bufferView")
          ->getSafeNumberOrDefault<int64_t>(0) == 1);

  REQUIRE(pDraco2->getValuePtrForKey("attributes"));
  REQUIRE(pDraco2->getValuePtrForKey("attributes")->isObject());
  REQUIRE(
      pDraco2->getValuePtrForKey("attributes")->getValuePtrForKey("POSITION"));
  REQUIRE(
      pDraco2->getValuePtrForKey("attributes")
          ->getValuePtrForKey("POSITION")
          ->getSafeNumberOrDefault<int64_t>(1) == 0);

  // Repeat test but this time the extension should not be deserialized at all.
  reader.getExtensions().setExtensionState(
      "KHR_draco_mesh_compression",
      CesiumJsonReader::ExtensionState::Disabled);

  GltfReaderResult result3 = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()),
      options);

  REQUIRE(result3.errors.empty());
  REQUIRE(result3.model.has_value());

  Model& model3 = result3.model.value();
  REQUIRE(model3.meshes.size() == 1);
  REQUIRE(model3.meshes[0].primitives.size() == 1);

  MeshPrimitive& primitive3 = model3.meshes[0].primitives[0];

  REQUIRE(!primitive3.getGenericExtension("KHR_draco_mesh_compression"));
  REQUIRE(!primitive3.getExtension<ExtensionKhrDracoMeshCompression>());
}

TEST_CASE("Extensions deserialize to JsonVaue iff "
          "a default extension is registered") {
  const std::string s = R"(
    {
        "asset" : {
            "version" : "2.0"
        },
        "extensions": {
            "A": {
              "test": "Hello World"
            },
            "B": {
              "another": "Goodbye World"
            }
        }
    }
  )";

  GltfReaderOptions options;
  GltfReader reader;
  GltfReaderResult withCustomExtModel = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()),
      options);

  REQUIRE(withCustomExtModel.errors.empty());
  REQUIRE(withCustomExtModel.model.has_value());

  REQUIRE(withCustomExtModel.model->extensions.size() == 2);

  JsonValue* pA = withCustomExtModel.model->getGenericExtension("A");
  JsonValue* pB = withCustomExtModel.model->getGenericExtension("B");
  REQUIRE(pA != nullptr);
  REQUIRE(pB != nullptr);

  REQUIRE(pA->getValuePtrForKey("test"));
  REQUIRE(
      pA->getValuePtrForKey("test")->getStringOrDefault("") == "Hello World");

  REQUIRE(pB->getValuePtrForKey("another"));
  REQUIRE(
      pB->getValuePtrForKey("another")->getStringOrDefault("") ==
      "Goodbye World");

  // Repeat test but this time the extension should be skipped.
  reader.getExtensions().setExtensionState(
      "A",
      CesiumJsonReader::ExtensionState::Disabled);
  reader.getExtensions().setExtensionState(
      "B",
      CesiumJsonReader::ExtensionState::Disabled);

  GltfReaderResult withoutCustomExt = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()),
      options);

  auto& zeroExtensions = withoutCustomExt.model->extensions;
  REQUIRE(zeroExtensions.empty());
}

TEST_CASE("Unknown MIME types are handled") {
  const std::string s = R"(
    {
        "asset" : {
            "version" : "2.0"
        },
        "images": [
            {
              "mimeType" : "image/webp"
            }
        ]
    }
  )";

  GltfReaderOptions options;
  GltfReader reader;
  GltfReaderResult result = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()),
      options);

  // Note: The result.errors will not be empty,
  // because no images could be read.
  REQUIRE(result.model.has_value());
}

TEST_CASE("Can parse doubles with no fractions as integers") {
  std::string s = R"(
    {
      "accessors": [
        {
          "count": 4.0,
          "componentType": 5121.0
        }
      ]
    }
  )";

  GltfReaderOptions options;
  GltfReader reader;
  GltfReaderResult result = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()),
      options);

  CHECK(result.warnings.empty());
  Model& model = result.model.value();
  CHECK(model.accessors[0].count == 4);
  CHECK(
      model.accessors[0].componentType ==
      Accessor::ComponentType::UNSIGNED_BYTE);
  s = R"(
    {
      "accessors": [
        {
          "count": 4.0,
          "componentType": 5121.1
        }
      ]
    }
  )";
  result = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()),
      options);
  CHECK(!result.warnings.empty());
}

TEST_CASE("Test KTX2") {
  std::filesystem::path gltfFile = CesiumGltfReader_TEST_DATA_DIR;
  gltfFile /= "CesiumBalloonKTX2Hacky.glb";
  std::vector<std::byte> data = readFile(gltfFile.string());
  CesiumGltfReader::GltfReader reader;
  GltfReaderResult result = reader.readGltf(data);
  REQUIRE(result.model);

  const Model& model = result.model.value();
  REQUIRE(model.meshes.size() == 1);
}

TEST_CASE("Can apply RTC CENTER if model uses Cesium RTC extension") {
  const std::string s = R"(
    {
      "extensions": {
          "CESIUM_RTC": {
              "center": [6378137.0, 0.0, 0.0]
          }
      }
    }
  )";

  GltfReaderOptions options;
  GltfReader reader;
  GltfReaderResult result = reader.readGltf(
      gsl::span(reinterpret_cast<const std::byte*>(s.c_str()), s.size()),
      options);
  REQUIRE(result.model.has_value());
  Model& model = result.model.value();
  const ExtensionCesiumRTC* cesiumRTC =
      model.getExtension<ExtensionCesiumRTC>();
  REQUIRE(cesiumRTC);
  std::vector<double> rtcCenter = {6378137.0, 0.0, 0.0};
  CHECK(cesiumRTC->center == rtcCenter);
}
