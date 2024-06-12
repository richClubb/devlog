Kubernetes Notes
----------------

https://www.cncf.io/phippy/phippy-goes-to-the-zoo-book/

Pods carry containers and do the bulk of the work, they are the environment on which the container runs

ReplicaSet - a grouping of pods, the replicaSet ensures that a certain number of pods are running and if one dies then it brings another online to replace it.

Not sure what the secrets are, but I'm guessing it's similar to and Azure KeyVault

Deployments are mechanisms for deploying sets of pods

DaemonSets provide a way to ensure that a copy of a Pod is running on every node in the cluster. - not sure, need to research more.

Ingresses are how outside entities access services inside the cluster.

CronJobs do specific tasks at specific times

CRDs (CustomResourceDefinitions) defines a custom resource type