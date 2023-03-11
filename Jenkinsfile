pipeline {
    agent none
    
    // options {
    //     // This is required if you want to clean before build
    //     skipDefaultCheckout(true)
    // }

    stages {
        stage('clear workspace') {
            agent any
            steps {
                // sh "rm -rf *"
                sh "ls"
                sh "pwd"
                sh "./linux/geberate.sh"
            }
        }
        
        stage('checkout') {
            agent any
            steps {
                checkout scm
            }
        }
        
        stage('configure') {
            agent { label 'linux' }
            steps {
                sh "./alexandrescu_advice/linux/generate.sh"
            }
        }

        stage('build') {
            agent { label 'linux' }
            steps {
                sh "./alexandrescu_advice/linux/build.sh"
            }
        }
        
        stage('test') {
            agent { label 'linux' }
            steps {
                sh "./alexandrescu_advice/linux/test.sh"
            }
        }
    }
}
