/**
 *  @file   PandoraPFANew/src/Managers/AlgorithmManager.cc
 * 
 *  @brief  Implementation of the algorithm manager class.
 * 
 *  $Log: $
 */

#include "Algorithms/ClusteringAlgorithm.h"
#include "Algorithms/PrimaryClusteringAlgorithm.h"
#include "Algorithms/PhotonClusteringAlgorithm.h"
#include "Algorithms/ReclusteringAlgorithm.h"

#include "Managers/AlgorithmManager.h"

#include "Xml/tinyxml.h"

namespace pandora
{

AlgorithmManager::AlgorithmManager(Pandora *pPandora) :
    m_pPandora(pPandora)
{
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, RegisterAlgorithmFactory("Clustering", new ClusteringAlgorithm::Factory));
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, RegisterAlgorithmFactory("PrimaryClustering", new PrimaryClusteringAlgorithm::Factory));
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, RegisterAlgorithmFactory("PhotonClustering", new PhotonClusteringAlgorithm::Factory));
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, RegisterAlgorithmFactory("Reclustering", new ReclusteringAlgorithm::Factory));
}

//------------------------------------------------------------------------------------------------------------------------------------------

AlgorithmManager::~AlgorithmManager()
{
    for (AlgorithmMap::iterator iter = m_algorithmMap.begin(), iterEnd = m_algorithmMap.end(); iter != iterEnd; ++iter)
        delete iter->second;

    for (AlgorithmFactoryMap::iterator iter = m_algorithmFactoryMap.begin(), iterEnd = m_algorithmFactoryMap.end(); iter != iterEnd; ++iter)
        delete iter->second;

    m_algorithmMap.clear();
    m_algorithmFactoryMap.clear();
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode AlgorithmManager::RegisterAlgorithmFactory(const std::string &algorithmType, AlgorithmFactory *const pAlgorithmFactory)
{
    if (!m_algorithmFactoryMap.insert(AlgorithmFactoryMap::value_type(algorithmType, pAlgorithmFactory)).second)
        return STATUS_CODE_ALREADY_PRESENT;

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode AlgorithmManager::InitializeAlgorithms(const TiXmlHandle *const pXmlHandle)
{
    for (TiXmlElement *pXmlElement = pXmlHandle->FirstChild("algorithm").Element(); NULL != pXmlElement;
        pXmlElement = pXmlElement->NextSiblingElement("algorithm"))
    {
        std::string algorithmName;
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, CreateAlgorithm(pXmlElement, algorithmName));
        m_pandoraAlgorithms.push_back(algorithmName);
    }

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode AlgorithmManager::CreateAlgorithm(TiXmlElement *const pXmlElement, std::string &algorithmName)
{
    std::string instanceLabel;
    const StatusCode statusCode = FindSpecificAlgorithmInstance(pXmlElement, algorithmName, instanceLabel);

    if (STATUS_CODE_NOT_FOUND != statusCode)
        return statusCode;

    AlgorithmFactoryMap::const_iterator iter = m_algorithmFactoryMap.find(pXmlElement->Attribute("type"));

    if (m_algorithmFactoryMap.end() == iter)
        return STATUS_CODE_NOT_FOUND;

    Algorithm *pAlgorithm = NULL;
    pAlgorithm = iter->second->CreateAlgorithm();

    if (NULL == pAlgorithm)
        return STATUS_CODE_FAILURE;

    pAlgorithm->m_algorithmType = iter->first;

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pAlgorithm->RegisterPandora(m_pPandora));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pAlgorithm->ReadSettings(TiXmlHandle(pXmlElement)));

    algorithmName = TypeToString(pAlgorithm);

    if (!m_algorithmMap.insert(AlgorithmMap::value_type(algorithmName, pAlgorithm)).second)
        return STATUS_CODE_FAILURE;

    if (!instanceLabel.empty() && !m_specificAlgorithmInstanceMap.insert(SpecificAlgorithmInstanceMap::value_type(instanceLabel, algorithmName)).second)
        return STATUS_CODE_FAILURE;

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode AlgorithmManager::FindSpecificAlgorithmInstance(TiXmlElement *const pXmlElement, std::string &algorithmName, std::string &instanceLabel) const
{
    try 
    {
        instanceLabel = std::string(pXmlElement->Attribute("instance"));
        SpecificAlgorithmInstanceMap::const_iterator iter = m_specificAlgorithmInstanceMap.find(instanceLabel);

        if (m_specificAlgorithmInstanceMap.end() == iter)
            return STATUS_CODE_NOT_FOUND;

        algorithmName = iter->second;

        AlgorithmMap::const_iterator targetIter = m_algorithmMap.find(algorithmName);

        if ((m_algorithmMap.end() == targetIter) || (targetIter->second->m_algorithmType != std::string(pXmlElement->Attribute("type"))))
            return STATUS_CODE_FAILURE;

        return STATUS_CODE_SUCCESS;
    }
    catch (...)
    {
        return STATUS_CODE_NOT_FOUND;
    }
}

} // namespace pandora
