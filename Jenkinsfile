pipeline {
    agent none
    
    stages {
        stage('clear workspace') {
            agent any
            steps {
                sh "rm -rf alexandrescu_advice"
            }
        }
        
        // stage('checkout sources') {
        //     agent any
        //     steps {
        //         checkout scm
        //     }
        // }
        
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
