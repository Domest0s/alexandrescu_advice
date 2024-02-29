pipeline {
    agent {
        docker {
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
