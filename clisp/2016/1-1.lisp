(if t
	;; real deal brother
	(progn

	  ;; Approach 1 - weird compilation error
	  ;; (defun read-instructions (filename)
	  ;; 	(mapcar
	  ;; 	 (lambda (instruction) (let ((cleaned (string-trim '(#\Space) instruction)))
	  ;; 							 (list (char cleaned 0) (parse-integer cleaned :start 1))))
	  ;; 	 (uiop:split-string (string-trim '(#\Newline #\Tab #\Space)
	  ;; 									 (let ((input (make-array 0 :element-type 'character :adjustable t)))
	  ;; 									   (with-open-file (stream filename)
	  ;; 										 (adjust-array input (file-length stream))
	  ;; 										 (read-sequence input stream))
	  ;; 									   input))
	  ;; 						:separator '(#\,))))

	  ;; (defun process-instruction (state instruction)
	  ;; 	(let* ((location (first state))
	  ;; 		   (direction (second state))
	  ;; 		   (turn (first instruction))
	  ;; 		   (amount (second instruction))
	  ;; 		   (new-direction (mod (if (eql turn #\L) (1- direction) (1+ direction)) 4))
	  ;; 		   (displacement (case new-direction
	  ;; 						   (0 (list 0 amount))
	  ;; 						   (1 (list amount 0))
	  ;; 						   (2 (list 0 (- amount)))
	  ;; 						   (3 (list (- amount) 0))))
	  ;; 		   (new-location (mapcar #'+ location displacement)))
	  ;; 	  (list new-location new-direction)))

	  ;; (let* ((instructions (read-instructions "../../inputs/2016/1"))
	  ;; 		 (final-state (reduce process-instruction instructions :initial-value '((0, 0) 0)))
	  ;; 		 (final-location (first final-state)))
	  ;; 	(format t "~%Total distance travelled was ~a" (reduce #'+ (mapcar #'abs final-location))))

	  ;; Approach 2
	  (let ((location '(0 0)) (direction 0))  ;; direction is represented like the hands of a clock, goes from 0 to 3
		(dolist (instruction-raw (let ((input (make-array 0 :element-type 'character :adjustable t)))
								   (with-open-file (stream "../../inputs/2016/1"
														   :direction :input
														   :if-does-not-exist :error)
									 (adjust-array input (file-length stream))
									 (read-sequence input stream))
								   (uiop:split-string (string-trim '(#\Newline #\Tab #\Space) input) :separator '(#\,))))
		  (let* ((instruction (string-trim '(#\Space) instruction-raw))
				 (direction-relative (char instruction 0))
				 (amount (parse-integer instruction :start 1))
				 (direction-new (mod (if (eql direction-relative #\L) (1- direction) (1+ direction)) 4))
				 (displacement (case direction-new
								 (0 (list 0 amount))
								 (1 (list amount 0))
								 (2 (list 0 (- amount)))
								 (3 (list (- amount) 0)))))
			(setq direction direction-new)
			(setq location (mapcar #'+ location displacement))
			(format t "~%~a ~a, ~a ~a, ~a" direction-relative amount direction displacement location)))
		(format t "~%Total distance travelled was ~a" (reduce #'+ (mapcar #'abs location)))
		)

	  )


	;; experimentation and learning
	(progn

	  (with-open-file (stream "/dev/shm/test.txt" :direction :input :element-type 'character)
		;; 0
		(dolist (item (list '(file-position lstream) '(probe-file lstream) '(directory lstream) '(file-write-date lstream)
							'(truename lstream) '(read-line lstream nil) '(file-author "/") '(file-length lstream)
							'(file-position lstream)))
		  (defparameter lstream stream)
		  (format t "~%~a = ~a " item (eval item)))

		;; 1
		(file-position stream 0)
		(let ((input (make-string (file-length stream) :initial-element #\~)))
		  (print "=================")
		  (read-sequence input stream)
		  input)

		;; 2
		(dotimes (_i 4)
		  (let* ((i _i) (b (1- i)) (a (1+ i)))
			(format t "~%~d | ~d -> ~d | ~d -> ~d" i b (mod b 4) a (mod a 4))))
		
		)

	  ))

