/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                INTEL CORPORATION PROPRIETARY INFORMATION                //
//   This software is supplied under the terms of a license agreement or   //
//  nondisclosure agreement with Intel Corporation and may not be copied   //
//   or disclosed except in accordance with the terms of that agreement.   //
//       Copyright (c) 2003 Intel Corporation. All Rights Reserved.        //
//                                                                         //
//  File:      pnlParEmLearningEngine.cpp                                  //
//                                                                         //
//  Purpose:   Implementation of the parallel version of EM parameter      //
//             learning algorithm for BNet                                 //
//                                                                         //
//  Author(s): (in alphabetical order)                                     //
//             Abrosimova, Chernishova, Gergel, Senin, Sysoyev, Vinogradov //
//             NNSU                                                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
  
#include "pnlConfig.hpp"
#include "pnlParEmLearningEngine.hpp"

#ifdef PAR_PNL

#include "pnlTabularDistribFun.hpp"
#include "pnlJtreeInferenceEngine.hpp"

#ifdef PAR_OMP
#include <omp.h>
#endif

#ifdef PAR_MPI
#include <mpi.h>
#endif

// ----------------------------------------------------------------------------

PNL_USING

CParEMLearningEngine* CParEMLearningEngine::Create(
    CStaticGraphicalModel *pGrModel)
{
    if(!pGrModel)
    {
        PNL_THROW(CNULLPointer, "Graphical Model");
    }

    CParEMLearningEngine *pNewEngine = 
        new CParEMLearningEngine(pGrModel, NULL, itParamLearnEM);

    return pNewEngine;
}
// ----------------------------------------------------------------------------

CParEMLearningEngine::~CParEMLearningEngine()
{
}
// ----------------------------------------------------------------------------

CParEMLearningEngine::CParEMLearningEngine(CStaticGraphicalModel *pGrModel,
    CInfEngine *pInfEng, ELearningTypes LearnType):CEMLearningEngine(pGrModel,
    pInfEng, LearnType)
{
}
// ----------------------------------------------------------------------------

#ifdef PAR_MPI
void CParEMLearningEngine::Learn()
{
    CStaticGraphicalModel *pGrModel =  this->GetStaticModel();
    PNL_CHECK_IS_NULL_POINTER(pGrModel);
    PNL_CHECK_LEFT_BORDER(GetNumEv() - GetNumberProcEv() , 1);

    CJtreeInfEngine *pCurrentInfEng = NULL;

    CFactor *parameter = NULL;
    int exit = 0;
    int numberOfParameters = pGrModel->GetNumberOfParameters();
    int domainNodes;
    int infIsNeed = 0;
    int itsML = 0;

    // !!!
    float loglik = -FLT_MAX;
    float loglikOld = -FLT_MAX;
    float epsilon = GetPrecisionEM();
    float stopExpression = epsilon + 1.0f;
    int iteration = 0;
    int currentEvidNumber;
    int bMaximize = 0;
    int bSumOnMixtureNode = 0;
    const CEvidence* pCurrentEvid;
    int start_mpi, finish_mpi;
    int NumberOfProcesses, MyRank;
    int numSelfEvidences;
    
    MPI_Comm_size(MPI_COMM_WORLD, &NumberOfProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);

    int d = 0;
    do
    {
        iteration++;

        numSelfEvidences = (GetNumEv() - GetNumberProcEv()) / NumberOfProcesses;
        start_mpi = GetNumberProcEv() + numSelfEvidences * MyRank; // !!!
        if (MyRank < NumberOfProcesses - 1)
            finish_mpi = start_mpi + numSelfEvidences; // !!!
        else
            finish_mpi = GetNumEv(); // !!!        

        for(int ev = start_mpi; ev < finish_mpi; ev++)
        {
            infIsNeed = 0;
            currentEvidNumber = ev; // !!!

            pCurrentEvid = m_Vector_pEvidences[currentEvidNumber];
            if( !pCurrentEvid)
            {
                PNL_THROW(CNULLPointer, "evidence")
            }

            infIsNeed = !GetObsFlags(ev)->empty(); // !!!

            if(infIsNeed)
            {
                // create inference engine
                if(!pCurrentInfEng)
                {
                    pCurrentInfEng = CJtreeInfEngine::Create(pGrModel);
                }
                pCurrentInfEng->EnterEvidence(pCurrentEvid, bMaximize,
                    bSumOnMixtureNode);
            }

            for(domainNodes = 0; domainNodes < numberOfParameters; domainNodes++)
            {
                parameter = pGrModel->GetFactor(domainNodes);
                if(infIsNeed)
                {
                    int DomainSize;
                    const int *domain;
                    parameter->GetDomain(&DomainSize, &domain);
                    if (IsDomainObserved(DomainSize, domain, currentEvidNumber))
                    {
                        const CEvidence *pEvidences[] = { pCurrentEvid };
                        parameter->UpdateStatisticsML(pEvidences, 1);
                    }
                    else
                    {
                        pCurrentInfEng->MarginalNodes(domain, DomainSize, 1);
                        const CPotential * pMargPot = pCurrentInfEng->GetQueryJPD();
                        parameter ->UpdateStatisticsEM(pMargPot, pCurrentEvid);
                    }
                }
                else
                {
                    const CEvidence *pEvidences[] = { pCurrentEvid };
                    parameter->UpdateStatisticsML(pEvidences, 1);
                }
            }
            itsML = itsML || !infIsNeed;
        }

        for(domainNodes = 0; domainNodes < numberOfParameters; domainNodes++ )
        {
            parameter = pGrModel->GetFactor(domainNodes);
            
            CNumericDenseMatrix<float> *matForSending;
            int matDim;
            const int *pMatRanges;
            int dataLength;
            const float *pDataForSending;

            matForSending = static_cast<CNumericDenseMatrix<float>*>
                ((parameter->GetDistribFun())->GetStatisticalMatrix(stMatTable));

            matForSending->GetRanges(&matDim, &pMatRanges);
            matForSending->GetRawData(&dataLength, &pDataForSending);
            float *pDataRecv = new float[dataLength];
            float *pDataRecv_copy = new float[dataLength];
            MPI_Status status;

            MPI_Allreduce((void*)pDataForSending, pDataRecv, dataLength, MPI_FLOAT, MPI_SUM,
                MPI_COMM_WORLD);

            CNumericDenseMatrix<float> *RecvMatrix =
                static_cast<CNumericDenseMatrix<float>*>
                (parameter->GetDistribFun()->GetStatisticalMatrix(stMatTable));
            int dataLength_new;
            float *pData_new;
            RecvMatrix->GetRawData(&dataLength_new, (const float**)(&pData_new));
            for(int t=0;t<dataLength_new;t++)
                pData_new[t]=pDataRecv[t];
        }
        switch (pGrModel->GetModelType())
        {
        case mtBNet:
            {
                loglikOld = loglik;
                loglik = 0.0f;
                for(domainNodes = 0; domainNodes < numberOfParameters; domainNodes++)
                {
                    parameter = pGrModel->GetFactor(domainNodes);
                    loglik += parameter->ProcessingStatisticalData(m_numberOfAllEvidences);
                }
                break;
            }
        case mtMRF2:
        case mtMNet:
            {
                loglikOld = loglik;
                loglik = _LearnPotentials();
                break;
            }
        default:
            {
                PNL_THROW(CBadConst, "model type")
                    break;
            }
        }

        stopExpression = 
            float(fabs(2 * (loglikOld - loglik) / (loglikOld + loglik)));
        exit = ((stopExpression > epsilon) && (iteration <= GetMaxIterEM())) && !itsML;
        if(exit)
        {
            ClearStatisticData();
        }

        delete pCurrentInfEng;
        pCurrentInfEng = NULL;
    }while(exit);

    if(iteration > GetMaxIterEM())
    {
        PNL_THROW(CNotConverged, "maximum number of iterations")
    }

    SetNumProcEv( GetNumEv() );
}
#endif // PAR_MPI
// ----------------------------------------------------------------------------

#ifdef PAR_OMP
void CParEMLearningEngine::LearnOMP()
{
    CStaticGraphicalModel *pGrModel =  this->GetStaticModel();
    PNL_CHECK_IS_NULL_POINTER(pGrModel);
    PNL_CHECK_LEFT_BORDER(GetNumEv() - GetNumberProcEv() , 1);

    //omp_set_num_threads(2);
    int numberOfThreads = omp_get_num_procs();
    //CParPearlInfEngine **pCurrentInfEng = new CParPearlInfEngine*[numberOfThreads];
    CJtreeInfEngine **pCurrentInfEng = new CJtreeInfEngine*[numberOfThreads];
    for (int i = 0; i < numberOfThreads; i++)
        pCurrentInfEng[i] = NULL;
    CFactor *parameter1 = NULL;

    int exit = 0;
    int numberOfParameters = pGrModel->GetNumberOfParameters();
    int domainNodes;
    //int itsML = 0;

    // !!!
    float loglik = -FLT_MAX;
    float loglikOld = -FLT_MAX;
    float epsilon = GetPrecisionEM();
    float stopExpression = epsilon + 1.0f;
    int iteration = 0;

    int ev;

    // to create additional factors
    CFactor **ppAllFactors = new CFactor*[numberOfParameters*numberOfThreads];
    bool *was_updated = new bool[numberOfParameters*numberOfThreads];
    int factor;

#pragma omp parallel for private(factor) default(shared)
    for (factor = 0; factor < numberOfParameters; factor++)
    {
        ppAllFactors[factor] = pGrModel->GetFactor(factor);
        ppAllFactors[factor]->GetDistribFun()->ClearStatisticalData();
        was_updated[factor] = false;
        for (int proc = 1; proc < numberOfThreads; proc++)
        {
            ppAllFactors[factor + proc * numberOfParameters] =
                ppAllFactors[factor]->Clone();
            ppAllFactors[factor + proc * numberOfParameters]->GetDistribFun()->
                ClearStatisticalData();
            was_updated[factor + proc * numberOfParameters]= false;
        };
    };

    int* itsML = new int[numberOfThreads];  
    for (int delta = 0; delta < numberOfThreads; delta++)
    {
        itsML[delta] = 0;
    };

    do
    {
        iteration++;

#pragma omp parallel for schedule(dynamic) private(ev)
        for (ev = GetNumberProcEv(); ev < GetNumEv() ; ev++)
        {  
            CFactor *parameter = NULL;
            int DomainNodes_new; 
            int bMaximize = 0;
            int bSumOnMixtureNode = 0;
            int infIsNeed = 0;
            int currentEvidNumber = ev; // !!!

            const CEvidence* pCurrentEvid = m_Vector_pEvidences[currentEvidNumber];

            infIsNeed = !GetObsFlags(ev)->empty(); // !!!

            int Num_thread = omp_get_thread_num();

            if (infIsNeed)
            {
                if (!pCurrentInfEng[Num_thread])
                {
                    pCurrentInfEng[Num_thread] = CJtreeInfEngine::Create(
                        (const CStaticGraphicalModel *)pGrModel);
                }
                pCurrentInfEng[Num_thread]->EnterEvidence(pCurrentEvid, bMaximize,
                    bSumOnMixtureNode);
            }
            for (DomainNodes_new = 0; DomainNodes_new < numberOfParameters; 
            DomainNodes_new++)
            {
                parameter = ppAllFactors[DomainNodes_new + 
                    Num_thread * numberOfParameters];
                if (infIsNeed)
                {
                    int DomainSize;
                    const int *domain;
                    parameter->GetDomain(&DomainSize, &domain);
                    if (IsDomainObserved(DomainSize, domain, currentEvidNumber))
                    {
                        const CEvidence *pEvidences[] = { pCurrentEvid };
                        parameter->UpdateStatisticsML(pEvidences, 1);
                        was_updated[DomainNodes_new+Num_thread*numberOfParameters]= true;
                    }
                    else
                    {
                        pCurrentInfEng[Num_thread]->MarginalNodes(domain, DomainSize, 1);
                        const CPotential * pMargPot = 
                            pCurrentInfEng[Num_thread]->GetQueryJPD();
                        parameter ->UpdateStatisticsEM(pMargPot, pCurrentEvid);
                        was_updated[DomainNodes_new+Num_thread*numberOfParameters]= true;
                    }
                }
                else
                {
                    const CEvidence *pEvidences[] = { pCurrentEvid };
                    parameter->UpdateStatisticsML(pEvidences, 1); 
                    was_updated[DomainNodes_new+Num_thread*numberOfParameters]= true;
                }  
            }
            itsML[Num_thread] = itsML[Num_thread] || !infIsNeed;
        }  // end of parallel for

        for (int delta = 1; delta < numberOfThreads; delta++)
        {
            itsML[0] = itsML[0] || itsML[delta];
        };

        //����������� ��������
#pragma omp parallel for private(factor) default(shared)
        for (factor = 0; factor < numberOfParameters; factor++)
        {
            for (int proc = 1; proc < numberOfThreads; proc++)
            {
                if (was_updated[factor+proc*numberOfParameters])
                {
                    ppAllFactors[factor]->UpdateStatisticsML(ppAllFactors[factor + 
                        proc*numberOfParameters]);
                    ppAllFactors[factor+proc*numberOfParameters]->GetDistribFun()->
                        ClearStatisticalData();
                };
                was_updated[factor+proc*numberOfParameters] = false;
            };
        };

        switch (pGrModel->GetModelType())
        {
        case mtBNet:
            {
                loglikOld = loglik;
                loglik = 0.0f;
                for (domainNodes = 0; domainNodes < numberOfParameters; domainNodes++)
                {
                    parameter1 = pGrModel->GetFactor(domainNodes);
                    loglik += parameter1->ProcessingStatisticalData(
                        m_numberOfAllEvidences);
                }
                break;
            }
        case mtMRF2:
        case mtMNet:
            {
                loglikOld = loglik;
                loglik = _LearnPotentials();
                break;
            }
        default:
            {
                PNL_THROW(CBadConst, "model type")
                    break;
            }
        }
        stopExpression = float(fabs(2 * (loglikOld - loglik) / 
            (loglikOld + loglik)));

        exit = ((stopExpression > epsilon) && (iteration <= GetMaxIterEM())) && !itsML[0];

        if (exit)
        {
            ClearStatisticData();
        }

        m_critValue.push_back(loglik);

        for (int j = 0; j < numberOfThreads; j++)
        {
            delete pCurrentInfEng[j];
            pCurrentInfEng[j] = NULL;
        }
    } while (exit);

    delete [] pCurrentInfEng;

    //�������� �������������� ��������
    for (factor = numberOfParameters; factor < numberOfParameters * numberOfThreads;
    factor++)
    {
        delete ppAllFactors[factor];
    };

    delete[] ppAllFactors;
    delete[] was_updated;

    if (iteration > GetMaxIterEM())
    {
        PNL_THROW(CNotConverged, "maximum number of iterations")
    }

    SetNumProcEv( GetNumEv() );
}
#endif // PAR_OMP
// ----------------------------------------------------------------------------

#ifdef PAR_RESULTS_RELIABILITY
bool pnl::EqualResults(CEMLearningEngine& eng1, CEMLearningEngine& eng2,
    float epsilon, int doPrint)
{
    int i, j, result = 1;
    CGraphicalModel *pGrModel1 = eng1.GetStaticModel();
    CGraphicalModel *pGrModel2 = eng2.GetStaticModel();
    int numberOfNodes = pGrModel1->GetNumberOfNodes();
    const float *output1;
    const float *output2;
    CNumericDenseMatrix<float> *pMatrix1;
    CNumericDenseMatrix<float> *pMatrix2;
    int length1 = 0; 
    int length2 = 0;
    int result1=1;

    for (i = 0; i < numberOfNodes; i++)
    {
        pMatrix1 = static_cast<CNumericDenseMatrix<float>*>(
            pGrModel1->GetFactor(i)->GetMatrix(matTable));
        pMatrix1->GetRawData(&length1, &output1);
        pMatrix2 = static_cast<CNumericDenseMatrix<float>*>(
            pGrModel2->GetFactor(i)->GetMatrix(matTable));
        pMatrix2->GetRawData(&length2, &output2);
        result1 = 1;
        for (int j = 0; j < length1; j++)
        {
            if (fabs(output1[j] - output2[j]) > epsilon)
            {
                result = 0;
                result1 = 0;
                break;
            }
        }
#if 0
        if (print)
        {
            if (result1)
                printf("%d\tOK", i);
            else
                printf("%d\tnot OK", i);
            printf("\n");
        }
#endif
    }

    return result;
}
#endif // PAR_RESULTS_RELIABILITY

#endif // PAR_PNL
// end of file ----------------------------------------------------------------