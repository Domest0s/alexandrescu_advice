pipeline {
    agent none
    options {
        skipDefaultCheckout()
    }

    stages {
        stage('checkout & clean') {
            agent any
            steps {
                // sh "rm -rf *"
                checkout scm
                sh "./linux/clean.sh"
            }
        }

        stage('configure') {
            agent { label 'linux' }
            steps {
                sh "./linux/generate.sh"
            }
        }

        stage('build') {
            agent { label 'linux' }
            steps {
                sh "./linux/build.sh"
            }
        }

        stage('test') {
            agent { label 'linux' }
            steps {
                sh "./linux/test.sh"
            }
        }
    }
}
