# installing Jenkins
https://www.jenkins.io/doc/book/installing/docker/

1. Create a bridge network in Docker using the following docker network create command:
```
docker network create jenkins
```

2. In order to execute Docker commands inside Jenkins nodes, download and run the docker:dind Docker image using the following docker run `run_dind.sh`.
```

# what is needed for agent

# Jenkins agent is a java app. It need jdk 8 or 11
```
$ sudo apt install openjdk-11-jre-headless
```

# to whitelist agent hosts on jenkins controller add 
```
$ ssh-keyscan 192.168.178.37 > /var/jenkins_home/.ssh/known_hosts
```
or, of DNS is setup correctly to resolve the domain name
$ ssh-keyscan 192.168.178.37 > /var/jenkins_home/.ssh/known_hosts


