pipeline {

    // https://www.jenkins.io/doc/book/pipeline/jenkinsfile/#handling-parameters
    parameters {
        string(name: 'cpuArch', description: 'agent CPU architecture (x86_64, arm64)')
    }

    agent {
        docker {
            label '${params.cpuArch}'
            image 'work_agent:WIP'
        }
    }

    options {
        skipDefaultCheckout()
        ansiColor('xterm')
    }

    stages {
        stage('checkout & clean') {
            steps {
                echo "aget is running ${params.cpuArch} World!"
                checkout scm
                sh "./linux/clean.sh"
            }
        }

        stage('configure') {
            steps {
                sh "./linux/generate.sh"
            }
        }

        stage('build') {
            steps {
                sh "./linux/build.sh"
            }
        }

        stage('test') {
            steps {
                sh "./linux/test.sh"
            }
        }
    }
}
