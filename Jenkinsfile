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
                sh "./linux/clean.sh"
            }
        }
        
        // stage('checkout') {
        //     agent any
        //     steps {
        //         checkout scm
        //     }
        // }
        
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
