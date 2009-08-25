/**
 *	@file	PandoraPFANew/include/Api/PandoraContentApi.h
 *
 * 	@brief	Header file for the pandora content api class.
 *
 *	$Log: $
 */
#ifndef PANDORA_CONTENT_API_H
#define PANDORA_CONTENT_API_H 1

#include "Pandora.h"

/**
 *	@brief	PandoraContentApi class
 */
class PandoraContentApi
{
public:
	/**
	 *	@brief	Cluster creation class
	 */
	class Cluster
	{
	public:
		/**
		 *	@brief	Create a cluster
		 *
		 *	@param	algorithm the algorithm creating the cluster
		 *	@param	pClusterParameters address of either 1) a single calo hit, 2) an input calo hit list, or 3) a track
		 */
		template <typename CLUSTER_PARAMETERS>
		static StatusCode Create(const pandora::Algorithm &algorithm, CLUSTER_PARAMETERS *pClusterParameters);
	};

	/**
	 *	@brief	Particle flow object creation class
	 */	
	class ParticleFlowObject
	{
	public:
		/**
		 *	@brief	Parameters class
		 */
		class Parameters
		{
		public:
			float						m_energy;			///< The particle flow object energy
			pandora::ClusterList		m_clusterList;		///< The clusters in the particle flow object
			pandora::TrackList			m_trackList;		///< The tracks in the particle flow object
		};
		
		/**
		 *	@brief	Create a particle flow object
		 * 
		 *	@param	algorithm the algorithm creating the particle flow object
		 *	@param	particleFlowObjectParameters the particle flow object parameters
		 */		 
		static StatusCode Create(const pandora::Algorithm &algorithm, const Parameters &parameters);
	};

	typedef ParticleFlowObject::Parameters ParticleFlowObjectParameters;

	/**
	 *	@brief	Match calo hits to their correct mc particles for particle flow
	 * 
	 *	@param	pandora the pandora instance containing the calo hits and mc particles
	 */
	static StatusCode MatchCaloHitsToMCPfoTargets(const pandora::Pandora &pandora);
	
	/**
	 *	@brief	Order input calo hits by pseudo layer
	 * 
	 *	@param	pandora the pandora instance containing the calo hits
	 */
	static StatusCode OrderInputCaloHits(const pandora::Pandora &pandora);

	/**
	 *	@brief	Run an algorithm registered with pandora
	 * 
	 *	@param	pandora the pandora instance with which the algorithm is registered
	 *	@param	algorithmName the algorithm name
	 */
	static StatusCode RunAlgorithm(const pandora::Pandora &pandora, const std::string &algorithmName);

	/**
	 *	@brief	Run an algorithm registered with pandora
	 * 
	 *	@param	algorithm address of the parent algorithm, now attempting to run a daughter algorithm
	 *	@param	algorithmName the algorithm name
	 */
	static StatusCode RunAlgorithm(const pandora::Algorithm &algorithm, const std::string &algorithmName);

	/**
	 *	@brief	Get the current cluster list
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	pClusterList to receive the address of the current cluster list
	 */
	static StatusCode GetCurrentClusterList(const pandora::Algorithm &algorithm, const pandora::ClusterList *&pClusterList);

	/**
	 *	@brief	Get the current cluster list
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	pClusterList to receive the address of the current cluster list
	 *	@param	clusterListName to receive the current cluster list name
	 */
	static StatusCode GetCurrentClusterList(const pandora::Algorithm &algorithm, const pandora::ClusterList *&pClusterList,
		std::string &clusterListName);

	/**
	 *	@brief	Get the current ordered calo hit list
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	pOrderedCaloHitList to receive the address of the current ordered calo hit list
	 */
	static StatusCode GetCurrentOrderedCaloHitList(const pandora::Algorithm &algorithm, const pandora::OrderedCaloHitList *&pOrderedCaloHitList);

	/**
	 *	@brief	Get the current ordered calo hit list
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	pOrderedCaloHitList to receive the address of the current ordered calo hit list
	 *	@param	orderedCaloHitListName to receive the current ordered calo hit list name
	 */
	static StatusCode GetCurrentOrderedCaloHitList(const pandora::Algorithm &algorithm, const pandora::OrderedCaloHitList *&pOrderedCaloHitList,
		std::string &orderedCaloHitListName);

	/**
	 *	@brief	Get the current track list
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	pTrackList to receive the address of the current track list
	 */
	static StatusCode GetCurrentTrackList(const pandora::Algorithm &algorithm, const pandora::TrackList *&pTrackList);

	/**
	 *	@brief	Get the current track list
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	pTrackList to receive the address of the current track list
	 *	@param	trackListName to receive the current track list name
	 */
	static StatusCode GetCurrentTrackList(const pandora::Algorithm &algorithm, const pandora::TrackList *&pTrackList,
		std::string &trackListName);

	/**
	 *	@brief	Initialize reclustering operations
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	inputTrackList the input track list
	 *	@param	inputClusterList the input cluster list
	 *	@param	originalClustersListName to receive the name of the list in which the original clusters are stored
	 */
	static StatusCode InitializeReclustering(const pandora::Algorithm &algorithm, const pandora::TrackList &inputTrackList,
		const pandora::ClusterList &inputClusterList, std::string &originalClustersListName);

	/**
	 *	@brief	End reclustering operations
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	selectedClusterListName the name of the list containing the chosen recluster candidates (or the original candidates)
	 */
	static StatusCode EndReclustering(const pandora::Algorithm &algorithm, const std::string &selectedClusterListName);

	/**
	 *	@brief	Run a clustering algorithm (an algorithm that will create new cluster objects)
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	clusteringAlgorithmName the name of the clustering algorithm to run
	 *	@param	pNewClusterList to receive the address of the new cluster list populated
	 */
	static StatusCode RunClusteringAlgorithm(const pandora::Algorithm &algorithm, const std::string &clusteringAlgorithmName, 
		const pandora::ClusterList *&pNewClusterList);
		
	/**
	 *	@brief	Run a clustering algorithm (an algorithm that will create new cluster objects)
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	clusteringAlgorithmName the name of the clustering algorithm to run
	 *	@param	pNewClusterList to receive the address of the new cluster list populated
	 *	@param	newClusterListName to receive the name of the new cluster list populated
	 */
	static StatusCode RunClusteringAlgorithm(const pandora::Algorithm &algorithm, const std::string &clusteringAlgorithmName, 
		const pandora::ClusterList *&pNewClusterList, std::string &newClusterListName);

	/**
	 *	@brief	Add a calo hit to a cluster
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	pCluster address of the cluster to modify
	 *	@param	pCaloHit address of the hit to add
	 */
	static StatusCode AddCaloHitToCluster(const pandora::Algorithm &algorithm, const pandora::Cluster *pCluster,
		const pandora::CaloHit *pCaloHit);

	/**
	 *	@brief	Delete a cluster and remove it from the current cluster list
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	pCluster address of the cluster to delete
	 */
	static StatusCode DeleteCluster(const pandora::Algorithm &algorithm, const pandora::Cluster *pCluster);

	/**
	 *	@brief	Merge two clusters, deleting the original clusters and removing them from the current cluster list
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	pClusterLhs address of the first cluster
	 *	@param	pClusterRhs address of the second cluster
	 */
	static StatusCode MergeAndDeleteClusters(const pandora::Algorithm &algorithm, const pandora::Cluster *pClusterLhs,
		const pandora::Cluster *pClusterRhs);

	/**
	 *	@brief	Save the current cluster list and remove the constituent hits from the current ordered calo hit list
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	newClusterListName the new cluster list name
	 */
	static StatusCode SaveClusterList(const pandora::Algorithm &algorithm, const std::string newClusterListName);

	/**
	 *	@brief	Save the current cluster list and remove the constituent hits from the current ordered calo hit list
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	newClusterListName the new cluster list name
	 *	@param	clustersToSave a subset of the current cluster list - only clusters in both this and the current
	 * 			cluster list will be saved
	 */		
	static StatusCode SaveClusterList(const pandora::Algorithm &algorithm, const std::string &newClusterListName,
		const pandora::ClusterList &clustersToSave);

	/**
	 *	@brief	Save the current cluster list under a new name; use this new list as a permanent replacement for the current
	 * 			list (will persist outside the current algorithm)
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	newClusterListName the new cluster list name
	 */
	static StatusCode SaveClusterListAndReplaceCurrent(const pandora::Algorithm &algorithm, const std::string &newClusterListName);
		
	/**
	 *	@brief	Save the current cluster list under a new name; use this new list as a permanent replacement for the current
	 * 			list (will persist outside the current algorithm)
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	newClusterListName the new cluster list name
	 *	@param	clustersToSave a subset of the current cluster list - only clusters in both this and the current
	 * 			cluster list will be saved
	 */
	static StatusCode SaveClusterListAndReplaceCurrent(const pandora::Algorithm &algorithm, const std::string &newClusterListName,
		const pandora::ClusterList &clustersToSave);
		
	/**
	 *	@brief	Save the current ordered calo hit list under a new name
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	newListName the new ordered calo hit list name
	 */
	static StatusCode SaveOrderedCaloHitList(const pandora::Algorithm &algorithm, const pandora::OrderedCaloHitList &orderedCaloHitList,
		const std::string &newListName);

	/**
	 *	@brief	Save the current ordered calo hit list under a new name; use this new list as a permanent replacement for the
	 * 			current list (will persist outside the current algorithm)
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	newListName the new ordered calo hit list name
	 */
	StatusCode SaveOrderedCaloHitListAndReplaceCurrent(const pandora::Algorithm &algorithm, 
		const pandora::OrderedCaloHitList &orderedCaloHitList, const std::string &newListName);

	/**
	 *	@brief	Save the current track list under a new name
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	newListName the new ordered calo hit list name
	 */
	StatusCode SaveTrackList(const pandora::Algorithm &algorithm, const pandora::TrackList &trackList, const std::string &newListName);

	/**
	 *	@brief	Save the current track list under a new name; use this new list as a permanent replacement for the current
	 * 			list (will persist outside the current algorithm)
	 * 
	 *	@param	algorithm the algorithm calling this function
	 *	@param	newListName the new track list name
	 */
	StatusCode SaveTrackListAndReplaceCurrent(const pandora::Algorithm &algorithm, const pandora::TrackList &trackList,
		const std::string &newListName);		
};

#endif // #ifndef PANDORA_CONTENT_API_H
