(if
 t  ;; to save on those precious indentations

 (progn
   (defun bounded? (location)
	 (every (lambda (x) (and (>= x 0) (< x 3))) location))

   (defun location-to-digit (location)
	 (1+ (+ (* (second location) 3) (first location))))

   (defun move-to-direction (move)
	 (case move
	   (#\U '(0 -1))
	   (#\D '(0 1))
	   (#\L '(-1 0))
	   (#\R '(1 0))))

   (let ((current-location '(1 1)) (final-digits '()))
	 (dolist (line (uiop:read-file-lines "../../inputs/2016/2"))
	   (loop :for move :across line :do
		 (let* ((direction (move-to-direction move))
				(new-location (mapcar #'+ current-location direction)))
		   (if (bounded? new-location) (setq current-location new-location))))
	   (setq final-digits (append final-digits (list (location-to-digit current-location)))))
	 (format t "~%~a is the code to unlock the door" final-digits))

   (defun diagonal2? (location)
	 (every (lambda (x) (not (equal x 0))) location)) 

   (defun bounded2? (location)
	 ;; (<= (+ (abs (first location)) (abs (second location))) 2))
	 (every (lambda (x) (< (abs x)
						   (if (diagonal2? location) 2 3)))
			location))

   (defun location-to-digit2 (location)
	 (let* ((location-normalized (mapcar #'+ '(2 2) (list (first location) (+ (second location)))))
			(index (+ (* (second location-normalized) 5) (first location-normalized))))
	   (case index
		 ;; first row
		 (2 #\1)
		 ;; second row
		 (6 #\2) (7 #\3) (8 #\4)
		 ;; third row
		 (10 #\5) (11 #\6) (12 #\7) (13 #\8) (14 #\9)
		 ;; fourth row
		 (16 #\A) (17 #\B) (18 #\C)
		 ;; fifth row
		 (22 #\D) (otherwise (error "Logic error: ~a ~a" index location)))))

   (let ((current-location '(-2 0)) (final-digits '()))
	 (dolist (line (uiop:read-file-lines "../../inputs/2016/2"))
	   (loop :for move :across line :do
		 (let* ((direction (move-to-direction move))
				(new-location (mapcar #'+ current-location direction)))
		   (if (bounded2? new-location) (setq current-location new-location))))
	   (setq final-digits (append final-digits (list (location-to-digit2 current-location)))))
	 (format t "~%~a is the code to unlock the door" final-digits))
   )

 (progn
   (let ((line (uiop:read-file-line "../../inputs/2016/2")))
	 (format t "~%~a: ~a" (length line) line)
	 (format t "~%Does it have newlines? ~a" (count #\Newline line)))
   (let ((lines (uiop:read-file-lines "../../inputs/2016/2")))
	 (format t "~%~a: ~a" (reduce #'+ (loop :for line :in lines :collect (length line))) lines))
   )

 )
	
